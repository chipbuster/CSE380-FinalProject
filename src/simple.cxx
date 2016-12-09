#include<cmath>
#include<iostream>
#include<vector>
#include<cassert>
#include<stdexcept>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include "progopt.h"
#include "simple.h"

using namespace std;


/******** SIMPLE EULER SOLUTIONS ************/

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

// Solve a full trajectory, recording values. initState should have the initial value
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

/********** GSL SOLUTIONS ******************/


/* Derivative function for GSL ODE module*/
int simple_func (double t, const double y[], double f[],
      void *params)
{
  (void)y;
  double* dParams = static_cast<double*>(params);
  double m = dParams[0];
  double n = dParams[1];
  f[0] = m * sin(t) + n * t * t * t;
  return GSL_SUCCESS;
}

/* Jabobian function for GSL ODE module */
int simple_jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)

{
  double* dParams = static_cast<double*>(params);
  double m = dParams[0];
  double n = dParams[1];
  gsl_matrix_view dfdy_mat
    = gsl_matrix_view_array (dfdy, 1, 1);
  gsl_matrix * matt = &dfdy_mat.matrix;
  gsl_matrix_set (matt, 0, 0, 0.0);
  dfdt[0] = m * cos(t) + 3 * n * t * t;
  return GSL_SUCCESS;
}

vector<Vec2> gsl_simple_trajectory(Vec2 initState,const progOptions::Options& opts)
{

  // Initialize the parts of GSL ODE that relate only to the problem.
  double params[2] = {4,2};
  gsl_odeiv2_system sys = {simple_func, simple_jac, 1, params};

  // Read in options and initial state
  double t = initState.t;
  double x = initState.x;
  int nsteps = opts.nsteps;
  double h = opts.stepSize;
  vector<Vec2> results = vector<Vec2>(nsteps);

  // Initialize the parts that rely on input
  double y[1]; y[0] = x;
  gsl_odeiv2_driver * d;

  switch(opts.solType){
    case progOptions::rk4: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4
                                        ,1e-6, 1e-6, 0.0);
      break;    
    case progOptions::rkck: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkck
                                     ,1e-6, 1e-6, 0.0);
      break;    
    case progOptions::rkf45: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys,  gsl_odeiv2_step_rkf45,1e-6, 1e-6, 0.0);
      break;    
    default: throw std::invalid_argument("Got non-RK solType in RK method");
  }


  for (int i = 0; i < nsteps; i++)
    { 
      // Runs a single-step iteration of the ODE
      int status = gsl_odeiv2_driver_apply_fixed_step (d, &t, h, 1, y);

      if (status != GSL_SUCCESS){
       throw std::runtime_error("gsl_odeiv2_driver encountered an error.");
      }
      
      results[i] = Vec2(y[0],t);    
    }

  gsl_odeiv2_driver_free (d);
  return results;
}

/************** ANALYTIC SOLUTIONS ********************/

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

/* Calculate the deviation of the numeric solution from the analytical one
 * at the last step of the numerical simulation */
double calcSimpleNumericalError(vector<Vec2> analytic, vector<Vec2> numeric){
  Vec2 lastAnalytic = analytic.back();
  Vec2 lastNumeric = numeric.back();

  return abs(lastAnalytic.x - lastNumeric.x);
}
