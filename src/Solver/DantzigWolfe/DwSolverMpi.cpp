/*
 * DwSolverMpi.cpp
 *
 *  Created on: Dec 5, 2016
 *      Author: kibaekkim
 */

//#define DSP_DEBUG
#include <DantzigWolfe/DwSolverMpi.h>
#include <DantzigWolfe/DwMasterTr.h>
#include <DantzigWolfe/DwMasterTrLight.h>
#include <DantzigWolfe/DwWorkerMpi.h>

DwSolverMpi::DwSolverMpi(
		DecModel*   model,   /**< model pointer */
		DspParams*  par,     /**< parameters */
		DspMessage* message, /**< message pointer */
		MPI_Comm    comm     /**< MPI communicator */):
DwSolverSerial(model, par, message), comm_(comm) {
	MPI_Comm_size(comm_, &comm_size_);
	MPI_Comm_rank(comm_, &comm_rank_);
}

DwSolverMpi::~DwSolverMpi() {
	comm_ = MPI_COMM_NULL;
}

DSP_RTN_CODE DwSolverMpi::init() {
	BGN_TRY_CATCH

	/** create worker */
	worker_ = new DwWorkerMpi(model_, par_, message_, comm_);

	if (comm_rank_ == 0) {
		/** create master */
		if (par_->getBoolParam("DW/TRUST_REGION")) {
			if (par_->getBoolParam("DW/MASTER/BRANCH_ROWS"))
				master_ = new DwMasterTr(worker_);
			else
				master_ = new DwMasterTrLight(worker_);
		} else
			master_ = new DwMaster(worker_);

		/** initialize master */
		DSP_RTN_CHECK_THROW(master_->init());

		/** create an Alps model */
		alps_ = new DspModel(master_);
	}
	END_TRY_CATCH_RTN(;,DSP_RTN_ERR)
	return DSP_RTN_OK;
}

DSP_RTN_CODE DwSolverMpi::solve() {
	BGN_TRY_CATCH
	if (comm_rank_ == 0) {
		DSP_RTN_CHECK_THROW(alps_->solve());

		/** send signal */
		int sig = DwWorkerMpi::sig_terminate;
		MPI_Bcast(&sig, 1, MPI_INT, 0, comm_);
		DSPdebugMessage("Rank 0 sent signal %d.\n", sig);
	} else {
		DSP_RTN_CHECK_THROW(dynamic_cast<DwWorkerMpi*>(worker_)->receiver());
	}
	END_TRY_CATCH_RTN(;,DSP_RTN_ERR)
	return DSP_RTN_OK;
}

DSP_RTN_CODE DwSolverMpi::finalize() {
	BGN_TRY_CATCH
	if (comm_rank_ == 0)
		DSP_RTN_CHECK_THROW(master_->finalize());
	END_TRY_CATCH_RTN(;,DSP_RTN_ERR)
	return DSP_RTN_OK;
}