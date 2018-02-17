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

//����� �������� �������
class CRenderTextureFollow
{
 protected:
  //�������� ����� ��������
  long CurrentPointer;//������� ����� �������� � �������
  long dPointer;//��� ���������
  vector<long> vector_TextureIndexFollow;//������������������ ������� �������
  long Mode;//����� ������
  //�������� ����������
  long ScrollLToR;//-1-�������� �����������
  long ScrollUToD;//-1-�������� �����������
  long SpeedLToR;//�������� �������� ����� �������
  long SpeedUToD;//�������� �������� ����� �����
  long Dx;//������� �������� � �������� 
  long Dy; 
 public:
  CRenderTextureFollow(void);//�����������
  ~CRenderTextureFollow(void);//����������
 public:
  void Load(FILE *File,CRenderTexture &cRenderTexture);//��������� �������� ��������
  void Release(void);//���������� ������
  void SetTextureMatrix(void);//���������� ������� ���������������
  void SetCurrentTexture(CRenderTexture &cRenderTexture);//������� ��������
  void Processing(void);//���������� �������� ��������
};
#endif