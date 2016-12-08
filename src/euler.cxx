#include<cmath>
#include<iostream>
#include<vector>

#include "progopt.h"
#include "euler.h"

using namespace std;

// Take a timestep using Euler's method, with the equation
// dx/dt = 4 sin(t) + 2 t^3
void euler_simple_timestep(Vec2& inp, const progOptions::Options& opts){
  double x = inp.x; 
  double t = inp.t;

  // Calculate updates according to Euler's method
  double dt = opts.stepSize;
  double dx = (4 * sin(t) + 2 * t * t * t) * dt;

  if(opts.debug){
    cout << "Advancing simulation: at x="<<x<<", t="<<t<<". After taking step"
         << "h="<<dt<<", we have x="<<x + dx<<", t="<<t + dt<<endl;
  }

  t += dt;
  x += dx;

  // Update state of solution
  inp.x = x; inp.t = t;

}

// Solve a full trajectory, recording values. state should have the initial value
vector<Vec2> euler_simple_trajectory(Vec2 initState, const progOptions::Options& opts){
  vector<Vec2> solPath;
  solPath.reserve(opts.nsteps);

  Vec2 state = initState;

  // Mutate the state
  for (int i = 0; i < opts.nsteps; i++){
     solPath[i] = state;
     euler_simple_timestep(state, opts);
  }

  return solPath;

}
