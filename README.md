# DSP
DSP is an open-source and parallel package that implements decomposition methods for **stochastic mixed-integer programming (SMIP)** problems. These are structured optimization problems considering uncertain scenario realizations s with probabilities p_s in the following form:

        minimize   c^T x + \sum_{s=1}^S p_s q_s^T y_s
        subject to   A x                              = b
                   T_s x +                    W_s y_s = h_s for s = 1, .., S
                   some x, y_s are integers

where x and y_s are decision variable vectors with dimensions n_1 and n_2, respectively, A, T_s and W_s are matrices of dimensions m_1 by n_1, m_2 by n_1 and m_2 by n_2, respectively, and c, q_s, b, and h_s are vectors of appropriate dimensions.

DSP provides **parallel** implementations for the following decomposition methods:
* Dual decomposition (with subgradient method and several bundle methods)
* Benders decomposition

The methods can be run on computing clusters and multi-core processors.

## Download

You can clone this repository in your preferred directory by typing:
```bash
git clone https://github.com/Argonne-National-Laboratory/DSP.git
```

## Installation

See [INSTALL.md](INSTALL.md)

## Interfaces

### Julia Interface

DSP can use Julia as a modeling interface for the computational experiments. Julia is a high level dynamic programming language for technical computing, with syntax that is familiar to users of other technical computing environments such as MATLAB and Python. Julia can be downloaded from http://julialang.org/downloads/ If Julia is successfully installed on your machine, then you can start the Julia command-line tool by typing
```bash
julia
```
Now we need to install four Julia packages required to run DSP in the Julia environment. The packages should be installed in the Julia command-line tool. Please update the package list of Julia by typing
```julia
Pkg.update();
```
* [JuMP.jl](https://github.com/JuliaOpt/JuMP.jl) is a algebraic modeling package in Julia for mathematical programming, which can be installed by the following Julia command:
```julia
    Pkg.add("JuMP");
```
* The [Dsp.jl](https://github.com/kibaekkim/Dsp.jl) package provides an interface to ``JuMP.jl``. DSPsolver.jl can be installed by the Julia command
```julia
    Pkg.clone("https://github.com/kibaekkim/Dsp.jl.git");
```
* [MPI.jl](https://github.com/JuliaParallel/MPI.jl) is an **optional** package to run DSP in parallel on high-performance computing machines using MPI library. This is an MPI interface package, which can be installed by the following Julia command. MPICH is required for this package.
```julia
    Pkg.add("MPI");
```

### Python Interface

Python interface will be automatically installed if ``python`` library is available on your machine.

## Example

You can find examples in subdirectory examples.


## Credits

DSP has been developed and is maintained by:
* [Kibaek Kim](http://mcs.anl.gov/~kibaekkim/), Mathematics and Computer Science Division, Argonne National Laboratory.
* [Victor M. Zavala](http://zavalab.engr.wisc.edu/), Department of Chemical and Biological Engineering, University of Wisconsin-Madison.

## Publications
* Kibaek Kim and Victor M. Zavala. "[Algorithmic innovations and software for the dual decomposition method applied to stochastic mixed-integer programs](http://www.optimization-online.org/DB_FILE/2015/06/4960.pdf)" Optimization Online, 2015
* Kibaek Kim and Victor M. Zavala. "[Large-Scale Stochastic Mixed-Integer Programming Algorithms for Power Generation Scheduling](http://dx.doi.org/10.1007/978-3-319-28752-2_18)" Alternative Energy Sources and Technologies, 2016
* Kibaek Kim, Fan Yang, Victor M. Zavala, and Andrew A. Chien. "[Data Centers as Dispatchable Loads to Harness Stranded Power](http://dx.doi.org/10.1109/TSTE.2016.2593607)" IEEE Transactions on Sustainable Energy, 2016

## Acknowledgements

This material is based upon work supported by the U.S. Department of Energy, Office of Science, under contract number DE-AC02-06CH11357. We gratefully acknowledge the computing resources provided on *Blues*, a high-performance computing cluster operated by the Laboratory Computing Resource Center at Argonne National Laboratory. We thank E. Michael Gertz and Stephen Wright for providing the [OOQP](http://pages.cs.wisc.edu/~swright/ooqp/) software package.


[![Analytics](https://ga-beacon.appspot.com/UA-64449559-2/DSP/README.md)](https://github.com/igrigorik/ga-beacon)

