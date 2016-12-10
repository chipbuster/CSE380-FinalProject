#ifndef CHARGED_H
#define CHARGED_H

#include<vector>

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
      void *params);

// GSL function to calculate the jacobian
int charged_jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params);

vector<Vec6> gsl_charged_trajectory(Vec6 initState,const progOptions::Options& opts);

#endif
