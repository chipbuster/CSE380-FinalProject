CSE 380 Final Project
=====================

Since VolRover has let us all down yet again, I'm rapidly switching tracks to
the precanned project. This is the repo for that project.

The project instructions can be found in canned\_project.pdf. I intend to
implement most of the project...though of course time constraints may apply.

## Report

The report can be found in the `report` directory as a PDF, along with 
its source Rmd file. The scripts to plot the output can be found in
`plotting`, though not all the source data is included due to file
size limitations of GitHub. 

## Simple ODE

The simple ODE that I'll be solving is dx/dt = 4 sin(t) + 2 t^3.

Its analytical solution is x(t) = - 4 cos(t) + t^4 / 2 + C

## Prerequisites

mkl
libgsl
libGRVY

## Compilation Instructions

Project is currently designed to compile on TACC systems (specifically,
stampede) only.

In order to compile this software, you need the following modules in your
environment:

  * gcc 4.7.1
  * grvy 0.32.0
  * gsl 1.15
  * mkl 13.0.2.146

To do this, run the following command:

```
ml gcc/4.7.1  grvy/0.32.0  gsl/1.15  mkl/13.0.2.146
```

Then run

```
  cd src
  make
```

This will produce an executable called `main.x`.

You can also run `make opt` to make an optimized version of the binary
(compiled under `-O3`) and `make debug` to make a debugging binary. You may
need to run `make clean` before `make`ing one of these variants.

## How to run the code

Options are configured by the `input.dat` file in the `src` directory. The
executable will, by default, attempt to parse options out of this file. You can
either edit this file directly or copy it and provide the name of the new file
as an argument to the program on the command line, e.g. `./main.x
new-input.dat`.

The options available are:

  * `problem`: an integer describing the problem to solve. 0 encodes the simple
    ODE (described at the top of this document). 1 encodes the charged particle
    in a vertical E-field (described in the pdf).
  * `solMethod`: which numerical method to use to solve the problem.

     * 0 : Euler Method
     * 1 : Runge-Kutta 4th order (rk4)
     * 2 : Runge-Kutta Cash-Karp (rkck)
     * 3 : Runge-Kutta-Fehlberg  (rkf45)

    Note that only certain combinations of these two variables are allowed:
    the simple problem can be solved with all of them, but the
    charged-particle problem can only be solved with the rk methods.

  * `stepSize`: the size of the step to take.
  * `nsteps`  : the number of steps to take.
  * verificationMode: When `true`, run in verification mode. This is
    only available for the simple problem. It compares the simple problem
    against its analytical solution and outputs the error between the
    numerical solution and the analytical one at the final step.
  * `debugMode`: When `true`, will output extra debugging information
    about what phase the program is in.

## Program parts:

####datatypes.cxx

Contains code for data, structs/classes, and conversions between them.

####euler.cxx

Contains code for running the Euler method on the simple ODE.

####main.cxx

Main. Duh.

####progopt.cxx

Contains code and classes for processing input parameters using GRVY.
