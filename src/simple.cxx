#include<cmath>
#include<iostream>
#include<vector>
#include<cassert>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include "progopt.h"
#include "simple.h"

using namespace std;

// Take a timestep using Euler's method, with the equation
// dx/dt = 4 sin(t) + 2 t^3
void euler_simple_timestep(Vec2& inp, const progOptions::Options& opts){
  double x = inp.x; 
  double t = inp.t;

  // Calculate updates according to Euler's method
  double dt = opts.stepSize;
  double dx = (4 * sin(t) + 2 * t * t * t) * dt;

  t += dt;
  x += dx;

  // Update state of solution
  inp.x = x; inp.t = t;
}

// Solve a full trajectory, recording values. state should have the initial value
vector<Vec2> euler_simple_trajectory(Vec2 initState, const progOptions::Options& opts){
  vector<Vec2> solPath = vector<Vec2>(opts.nsteps);
  Vec2 state = initState;

  // Mutate the state
  for (int i = 0; i < opts.nsteps; i++){
     solPath[i] = state;
     euler_simple_timestep(state, opts);
  }

  return solPath;
}

double calcAnalyticSolution(double t, double C){
  return -4 * cos(t) + ((t*t)*(t*t) / 2) - C;
}

// Only called in verification mode. The analytic solution is
// x(t) = -4 cos(t) + t^4 / 2 + C
vector<Vec2> analytical_solution(const vector<Vec2>& numericalSolutionPath){
  vector<Vec2> analyticalSolution = vector<Vec2>(numericalSolutionPath.size());

  // Calculate C based on the first point
  double firstT = numericalSolutionPath[0].t;
  double firstX = numericalSolutionPath[0].x;
  double C = -4 * cos(firstT) + pow(firstT,4) / 2 - firstX;

  assert(abs(calcAnalyticSolution(firstT, C) - firstX) < 1e-2
        && "Something is wrong with the calculation of C");

  // For each entry in the numerical solution path, obtain its time value and
  // use it to find the analytical solution.
  
  for(size_t j = 0; j < numericalSolutionPath.size(); j++){
    double time = numericalSolutionPath[j].t;
    double sol = calcAnalyticSolution(time, C);
    analyticalSolution[j] = Vec2(sol,time);
  }

  return analyticalSolution;
}

