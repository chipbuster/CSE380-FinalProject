CSE 380 Final Project
=====================

Since VolRover has let us all down yet again, I'm rapidly switching tracks to
the precanned project. This is the repo for that project.

The project instructions can be found in canned\_project.pdf. I intend to
implement most of the project...though of course time constraints may apply.

## Simple ODE

The simple ODE that I'll be solving is dx/dt = 4 sin(t) + 2 t^3.

Its analytical solution is x(t) = - 4 cos(t) + t^4 / 2 + C

## Prerequisites

mkl
libgsl
libGRVY

## Compilation Instructions

Project is currently designed to compile on TACC systems (specifically, stampede) only.

In order to compile this software, you need the following modules in your environment:

```
xalt/0.6   TACC   gcc/4.7.1  grvy/0.32.0  gsl/1.15  mkl/13.0.2.146
```

## How to run the code

Also coming soon!

## Program parts:

####datatypes.cxx

Contains code for data, structs/classes, and conversions between them.

####euler.cxx

Contains code for running the Euler method on the simple ODE.

####main.cxx

Main. Duh.

####progopt.cxx

Contains code and classes for processing input parameters using GRVY.
