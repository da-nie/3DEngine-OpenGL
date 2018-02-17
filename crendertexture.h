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
//����� ������� �������
//----------------------------------------------------------------------------------------------------
class CRenderTexture
{
 protected:
  vector<long> vector_TextureEnabledIndex;//������ ������� ������������ �������
  GLuint *TextureList_Array;//������ ������� OpenGL
 public:
  CRenderTexture(void);//�����������
  ~CRenderTexture(void);//����������
 public:
  void Release(void);//���������� �������
  long AddEnabledTextureIndex(long texture_index);//�������� � ������ ������������ ��� ���� �������� (���������� � ����� � ������)
  bool LoadAndBuildGLTexture(char *FileName);//��������� �������� � ���������� �� � OpenGL
  bool SelectTexture(long texture_index);//������� �������� � �������� texture_index �� ������ ������������
};
#endif
