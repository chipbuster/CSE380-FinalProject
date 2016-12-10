#include "datatypes.h"
#include<iostream>

using std::vector;
using std::size_t;

Vec2::Vec2(){
  x = 0; t = 0;
}

Vec2::Vec2(double x1, double t1){
    x = x1; t = t1;
}

vector<double> Vec2::toVector(){
  vector<double> retval = vector<double>(2,0);
  retval[0] = this->x;
  retval[1] = this->t;
  return retval;
}

Vec6::Vec6(){
  x = 0; y = 0; z = 0;
  u = 0; v = 0; w = 0;
}

Vec6::Vec6(double x1, double y1, double z1, double u1, double v1, double w1){
  x = x1; y = y1; z = z1;
  u = u1; v = v1; w = w1;
}

vector<double> Vec6::toVector(){
  vector<double> retval = vector<double>(6,0);
  retval[0] = this->x;
  retval[1] = this->y;
  retval[2] = this->z;
  retval[3] = this->u;
  retval[4] = this->v;
  retval[5] = this->w;
  return retval;
}


// Collapse vector-of-Vec2 to vector-of-vectors
vector<vector<double> > collapseSolution(vector<Vec2> input){
  vector<vector<double> > out = vector<vector<double> >(input.size());
  for (size_t j = 0; j < input.size(); j++){
    out[j] = input[j].toVector();
  }

  return out;
}

// Collapse vector-of-Vec6 to vector-of-vectors (overloaded)
vector<vector<double> > collapseSolution(vector<Vec6> input){
  vector<vector<double> > out = vector<vector<double> >(input.size());
  for (size_t j = 0; j < input.size(); j++){
    out[j] = input[j].toVector();
  }

  return out;
}
