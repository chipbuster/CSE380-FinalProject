#ifndef DATATYPE_H
#define DATATYPE_H

#include<vector>

using std::vector;

// Wrapper classes to make interfacing with data a little less shitty
struct Vec2{
  double x,t;

  Vec2();
  Vec2(double x1, double t1);

  vector<double> toVector();
};

struct Vec6{

  double x,y,z,u,v,w;

  Vec6(double x1, double y1, double z1, double u1, double v1, double w1);
  Vec6();

  vector<double> toVector();
};

vector<vector<double> > collapseSolution(vector<Vec2> input);
vector<vector<double> > collapseSolution(vector<Vec6> input);

#endif
