#include "mathematic.h"
 
 
long GetPosition(float x,float y,float x1,float y1,float x2,float y2)
{
 float p=x*(y1-y2)-y*(x1-x2)+x1*y2-x2*y1;
 if (p<-EPS_DOUBLE) p=-1;
 if (p>EPS_DOUBLE) p=1;
 if (p>=-EPS_DOUBLE && p<=EPS_DOUBLE) p=0;
 return((long)(p));
}
bool Intersection(float xa1,float ya1,float xa2,float ya2,float xb1,float yb1,float xb2,float yb2,float* xo,float* yo)
{
 float lx=xa2-xa1;
 float ly=ya2-ya1;
 float kx=xb2-xb1;
 float ky=yb2-yb1;
 float xl=xa1;
 float yl=ya1;
 float xk=xb1;
 float yk=yb1;
 float d=-ly*kx+lx*ky;//определитель
 if (d==0) return(false);//не пересекаютс€
 float d1=(ly*xl-lx*yl)*(-kx)+lx*(ky*xk-kx*yk);
 float d2=ly*(ky*xk-kx*yk)-ky*(ly*xl-lx*yl);
 float xot=d1/d;//решаем методом  рамера
 float yot=d2/d;
 *xo=xot;
 *yo=yot;
 return(true);
}
bool Perpendicular(float x1,float y1,float x2,float y2,float xp,float yp,float *xo,float *yo)
{
 float x,y;
 if (x2-x1!=0)
 {
  float k=(y2-y1)/(x2-x1);
  x=(xp+(yp+k*x1-y1)*k)/(k*k+1);
  y=k*(x-x1)+y1;
 }
 else
 {
  x=x1;
  y=yp;
 }
 *xo=x;
 *yo=y;
 if (x>x1 && x>x2) return(false);//перпендикул€р не лежит на пр€мой
 if (x<x1 && x<x2) return(false);//перпендикул€р не лежит на пр€мой
 if (y>y1 && y>y2) return(false);//перпендикул€р не лежит на пр€мой
 if (y<y1 && y<y2) return(false);//перпендикул€р не лежит на пр€мой
 return(true);
}
 
 
