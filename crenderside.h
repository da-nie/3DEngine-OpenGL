#ifndef CRENDER_SIDE_H
#define CRENDER_SIDE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include "formats.h"
#include "crenderfragment.h"
#include "crendertexture.h"
#include "crendertexturefollow.h"
#include "crenderlighting.h"

#include <vector>
using namespace std;

//класс граней
class CRenderSide
{
 public:
  long Location;//положение
  //смещение грани от исходного положения
  float TX;
  float TY;
  float TZ;
  //нормаль
  float N_X;
  float N_Y;
  float N_Z;
  //эмиссия
  float Emission_R;
  float Emission_G;
  float Emission_B;
  //полупрозрачность
  bool Blend;
  //анимация текстуры
  CRenderTextureFollow cRenderTextureFollow;
  //источники света
  long LightingAmount;//их число
  long LightingArray[8];//их номера
  //список фрагментов грани
  vector<CRenderFragment> vector_CRenderFragment;
  //--------------------------------------------------
  //конструктор
  //--------------------------------------------------
  CRenderSide(void);
  //--------------------------------------------------
  //деструктор
  //--------------------------------------------------
  ~CRenderSide(void);
  //--------------------------------------------------
  //методы
  //--------------------------------------------------
  void Draw(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//нарисовать грань
  void SetBlend(bool blend);//установить прозрачность
  void SetTextureFollow(CRenderTextureFollow cRenderTextureFollow_Set);//установить анимацию текстуры
  void SetLocation(long location);//установить положение
  long GetLocation(void);//получить положение
  void Load(FILE *File);//загрузить грань
  void Release(void);//уничтожить грань
  void Translate(float VX,float VY,float VZ);//перенести грань на вектор (VX,VY,VZ) из оригинального положения
  void Processing(void);//внутренняя обработка данных грани (текстуры и т.д.)
  void CreateList(long &list);//создать списоки
};

#endif