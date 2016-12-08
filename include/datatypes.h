#ifndef DATATYPE_H
#define DATATYPE_H

struct Vec2{
  double x,t;

  Vec2(double x1, double t1){
    x = x1; t = t1;
  }
};

struct Vec6{
  double x,y,z,u,v,w;

  Vec6(double x1, double y1, double z1, double u1, double v1, double w1){
    x = x1; y = y1; z = z1; u = u1; v = v1; w = w1;
 }
};

#endif
