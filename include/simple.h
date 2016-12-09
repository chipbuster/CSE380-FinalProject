#ifndef EULER_H
#define EULER_H
#include<vector>

#include "progopt.h"
#include "datatypes.h"

void euler_simple_timestep(Vec2& inp, const progOptions::Options& opts);

std::vector<Vec2> euler_simple_trajectory(Vec2 state, const progOptions::Options& opts);

std::vector<Vec2> analytical_solution(const std::vector<Vec2>& numericalSolutionPath);

double calcAnalyticSolution(double t, double C);

double calcSimpleNumericalError(vector<Vec2> analytic, vector<Vec2> numeric);

#endif
