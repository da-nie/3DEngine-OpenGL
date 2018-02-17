#ifndef CRENDER_TEXTURE_H
#define CRENDER_TEXTURE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include <vector>
using namespace std;

#include "formats.h"

//----------------------------------------------------------------------------------------------------
//класс массива текстур
//----------------------------------------------------------------------------------------------------
class CRenderTexture
{
 protected:
  vector<long> vector_TextureEnabledIndex;//список номеров используемых текстур
  GLuint *TextureList_Array;//список текстур OpenGL
 public:
  CRenderTexture(void);//конструктор
  ~CRenderTexture(void);//деструктор
 public:
  void Release(void);//освободить ресурсы
  long AddEnabledTextureIndex(long texture_index);//добавить в список используемых ещё одну текстуру (возвращает её номер в списке)
  bool LoadAndBuildGLTexture(char *FileName);//загрузить текстуры и подключить их к OpenGL
  bool SelectTexture(long texture_index);//выбрать текстуру с индексом texture_index из списка используемых
};
#endif
