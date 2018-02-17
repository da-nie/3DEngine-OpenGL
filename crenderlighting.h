#ifndef CRENDER_LIGHTING_H
#define CRENDER_LIGHTING_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include "formats.h"

#include <vector>
using namespace std;

//класс источников света 
class CRenderLighting
{
 protected:
  struct SLighting
  {
   //коорлинаты
   float X;
   float Y;
   float Z;
   //цвет
   float R;
   float G;
   float B;   
   long Mode;//режим работы
   long TimeInterval;//интервал времени работы источника (на нём работает источник)
   float Mode2_DarkTime;
   float Mode2_LightTime;
   float Mode2_MinimumLightLevel;
   float Mode3_MinimumLightLevel;
   float Mode3_CycleTime;
   float Mode4_OnTime;
   float Mode4_OffTime;
   float Mode4_MinimumLightLevel;
   //резервные данные
   float Reserv_R;
   float Reserv_G;
   float Reserv_B;
   //рабочие данные
   float Brightness;
   float DeltaBrightness;
   long CurrentTime;//текущее время на интервале
  };
  vector<SLighting> vector_SLighting;//источники света
 public:
  CRenderLighting(void);//конструктор
  ~CRenderLighting(void);//деструктор
 public:
  void Release(void);//удалить источники света
  void Load(FILE *File);//загрузить источники света
  void SetGLLightingParameters(long index,long gllighting);//установить параметры источника OpenGL в состояние источника index
  void Processing(void);//произвести анимацию источников света
};
#endif
