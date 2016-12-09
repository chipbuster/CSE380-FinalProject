#include<cmath>
#include<iostream>
#include<vector>
#include<cassert>
#include<stdexcept>
#include<cstring>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include "progopt.h"
#include "simple.h"

using namespace std;

/* Charged particle system:
 * parameters: omega, tau
 *    x' = u
 *    y' = v
 *    z' = w
 *    u' = omega * v - u / tau
 *    v' = -omega * u - v / tau
 *    w' = -w / tau
*/

/* Mapping of variables into arrays:
 *    x = y[0]          x' = f[0]
 *    y = y[1]          y' = f[1]
 *    z = y[2]          z' = f[2]
 *    u = y[3]          u' = f[3]
 *    v = y[4]          v' = f[4]
 *    w = y[5]          w' = f[5]
*/

// GSL function to calculate the RHS
int charged_func (double t, const double y[], double f[],
      void *params)
{
  double* dParams = static_cast<double*>(params);
  double omega = dParams[0];
  double tau = dParams[1];

  f[0] = y[3];
  f[1] = y[4];
  f[2] = y[5];
  f[3] = omega * y[4] - y[3] / tau;
  f[4] = -omega * y[3] - y[4] / tau;
  f[5] = -y[5] / tau;

  return GSL_SUCCESS;
}

// GSL function to calculate the jacobian
int charged_jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  double* dParams = static_cast<double*>(params);
  double omega = dParams[0];
  double tau = dParams[1];
  gsl_matrix_view dfdy_mat
    = gsl_matrix_view_array (dfdy, 6, 6);
  gsl_matrix * matt = &dfdy_mat.matrix;
  
  /* To avoid explicitly zeroing lots and lots of things, zero the matrix
   * first and only explcitly set nonzero elements. */
  gsl_matrix_set_zero(matt);

  gsl_matrix_set (matt, 0, 3, 1.0); // dx'/du = 1, all others 0
  gsl_matrix_set (matt, 1, 4, 1.0); // dy'/dv = 1, all others 0
  gsl_matrix_set (matt, 2, 5, 1.0); // dz'/dw = 1, all others 0

  // Set matrix entries for u' 
  gsl_matrix_set (matt, 3, 3, - (1/tau));  // du'/du = -1 / tau
  gsl_matrix_set (matt, 3, 4, omega);      //du'/dv = omega

  // Set matrix entries for v'
  gsl_matrix_set (matt, 4, 3, -omega);     //dv'/du = -omega
  gsl_matrix_set (matt, 4, 4, -(1/tau));   //dv'/dv = -1/tau
  
  // Only one matrix entry for w'
  gsl_matrix_set (matt, 5, 5, -(1/tau));     //dw'/dw = -1/tau

  // None of the derivatives have explicit dependence on t
  memset(dfdt, 6, sizeof(double));
  
  return GSL_SUCCESS;
}


// Main driver
vector<Vec6> gsl_charged_trajectory(Vec6 initState,const progOptions::Options& opts)
{
  // Initialize the parts of GSL ODE that relate only to the problem.

  // "You can assume omega and tau are both set to the value of 5"
  double params[2] = {5.0,5.0};
  gsl_odeiv2_system sys = {charged_func, charged_jac, 6, params};

  // Read in options and initial state
  int nsteps = opts.nsteps;
  double h = opts.stepSize;
  vector<Vec6> results = vector<Vec6>(nsteps);

  // Initialize the parts that rely on input
  double y[6];
  y[0] = initState.x;
  y[1] = initState.y;
  y[2] = initState.z;
  y[3] = initState.u;
  y[4] = initState.v;
  y[5] = initState.w;
  gsl_odeiv2_driver * d;

  // Driver requires several variables that we won't really use.
  const double dummyHStart = h;
  const double dummyEpsAbs = 1e100;
  const double dummyEpsRel = 1e100;
  switch(opts.solType){
    case progOptions::rk4: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4
                                        ,dummyHStart,dummyEpsAbs,dummyEpsRel);
      break;    
    case progOptions::rkck: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkck
                                        ,dummyHStart,dummyEpsAbs,dummyEpsRel);
      break;    
    case progOptions::rkf45: 
      d = gsl_odeiv2_driver_alloc_y_new (&sys,  gsl_odeiv2_step_rkf45
                                        ,dummyHStart,dummyEpsAbs,dummyEpsRel);
      break;    
    default: throw std::invalid_argument("Got non-RK solType in RK method");
  }


  for (int i = 0; i < nsteps; i++)
    { 
      // Runs a single-step iteration of the ODE
      int status = gsl_odeiv2_driver_apply_fixed_step (d, &t, h, 1, y);

      if (status != GSL_SUCCESS){
       cout << gsl_strerror(status) << endl;
       throw std::runtime_error(gsl_strerror(status));
      }

      results[i] = Vec6(y[0],y[1],y[2],y[3],y[4],y[5]);    
    }

  gsl_odeiv2_driver_free (d);
  return results;
}
