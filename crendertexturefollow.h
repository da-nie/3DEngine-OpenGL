#ifndef CRENDER_TEXTURE_FOLLOW_H
#define CRENDER_TEXTURE_FOLLOW_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include <vector>
using namespace std;

#include "formats.h"
#include "crendertexture.h"

//класс анимации текстур
class CRenderTextureFollow
{
 protected:
  //анимация смены текстуры
  long CurrentPointer;//текущий номер текстуры в массиве
  long dPointer;//его изменение
  vector<long> vector_TextureIndexFollow;//последовательность номеров текстур
  long Mode;//режим работы
  //анимация скроллинга
  long ScrollLToR;//-1-обратное направление
  long ScrollUToD;//-1-обратное направление
  long SpeedLToR;//скорость движения слева направо
  long SpeedUToD;//скорость движения снизу вверх
  long Dx;//текущие смещения в текстуре 
  long Dy; 
 public:
  CRenderTextureFollow(void);//конструктор
  ~CRenderTextureFollow(void);//деструктор
 public:
  void Load(FILE *File,CRenderTexture &cRenderTexture);//загрузить анимацию текстуры
  void Release(void);//освободить память
  void SetTextureMatrix(void);//установить матрицу текстурирования
  void SetCurrentTexture(CRenderTexture &cRenderTexture);//выбрать текстуру
  void Processing(void);//произвести анимацию текстуры
};
#endif