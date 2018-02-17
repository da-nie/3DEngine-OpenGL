#ifndef MATHEMATIC_H
#define MATHEMATIC_H
 
#include <math.h>
 
#define M_PI 3.141592654
#define EPS 0.001
#define EPS_DOUBLE 0.00001
 
long GetPosition(float x,float y,float x1,float y1,float x2,float y2);
bool Intersection(float xa1,float ya1,float xa2,float ya2,float xb1,float yb1,float xb2,float yb2,float* xo,float* yo);
bool Perpendicular(float x1,float y1,float x2,float y2,float xp,float yp,float *xo,float *yo);
 
#endif
