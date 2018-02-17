#ifndef COMMON_H
#define COMMON_H
 
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <vector>
using namespace std;

#include "crenderfragment.h"
#include "csector.h"
 
#define FPS2 30.0
 
#define WIDTH_SCREEN 1024		
#define HEIGHT_SCREEN 768

//параметры порталов
struct SPortalComponent
{
 CSector *cSectorPtr;//указатель на сектор
 float X,Y;//координаты точки(она общая для этих прямых)
 //первая прямая отсечения общей зоны видимости
 float VL1_X,VL1_Y;//направляющий вектор
 //вторая прямая отсечения
 float VL2_X,VL2_Y;//направляющий вектор
  
 //первая прямая отсечения
 float L1_X,L1_Y;//направляющий вектор
 //вторая прямая отсечения
 float L2_X,L2_Y;//направляющий вектор
 //прямая ограничения области видимости
 float X1,Y1;
 float X2,Y2;
};

//параметры тумана
struct SFogSetting
{
 float R;
 float G;
 float B;
 float Density;
 long Enable;
};
 
 
#endif
