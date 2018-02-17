#ifndef CRENDER_FRAGMENT_H
#define CRENDER_FRAGMENT_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>

#include "formats.h"
#include "libext.h"

#include <vector>
using namespace std;

//����� ����������
class CRenderFragment
{
 protected:
  bool LightingState[8];//��������� ���������� ����� (true - �������� �������)
  GLuint List;//����� ������ ��� ��������� ���������
  long Vertex;//����� ������ �������� ���������
  //��� ���������� ����� ������ ��� ��������� ������
  struct SVertex
  {
   //���������� ��������
   float X;
   float Y;
   float Z;
   //���������� ���������� ��������
   float TU;
   float TV;
  };
  vector<SVertex> vector_SVertex;//���������� ������ ���������
  //������� ���������
  float N_X;
  float N_Y;
  float N_Z;
 public:
  CRenderFragment(void);//�����������
  ~CRenderFragment(void);//����������
 public:
  void Draw(void);//���������� ��������
  void Load(FILE *File);//��������� ��������
  void Release(void);//������� ��������
  void SetNormal(float nx,float ny,float nz);//������ �������
  void CreateList(long &list);//������� ������  � ������� list
};
#endif
