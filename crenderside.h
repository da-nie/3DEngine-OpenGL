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

//����� ������
class CRenderSide
{
 public:
  long Location;//���������
  //�������� ����� �� ��������� ���������
  float TX;
  float TY;
  float TZ;
  //�������
  float N_X;
  float N_Y;
  float N_Z;
  //�������
  float Emission_R;
  float Emission_G;
  float Emission_B;
  //����������������
  bool Blend;
  //�������� ��������
  CRenderTextureFollow cRenderTextureFollow;
  //��������� �����
  long LightingAmount;//�� �����
  long LightingArray[8];//�� ������
  //������ ���������� �����
  vector<CRenderFragment> vector_CRenderFragment;
  //--------------------------------------------------
  //�����������
  //--------------------------------------------------
  CRenderSide(void);
  //--------------------------------------------------
  //����������
  //--------------------------------------------------
  ~CRenderSide(void);
  //--------------------------------------------------
  //������
  //--------------------------------------------------
  void Draw(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//���������� �����
  void SetBlend(bool blend);//���������� ������������
  void SetTextureFollow(CRenderTextureFollow cRenderTextureFollow_Set);//���������� �������� ��������
  void SetLocation(long location);//���������� ���������
  long GetLocation(void);//�������� ���������
  void Load(FILE *File);//��������� �����
  void Release(void);//���������� �����
  void Translate(float VX,float VY,float VZ);//��������� ����� �� ������ (VX,VY,VZ) �� ������������� ���������
  void Processing(void);//���������� ��������� ������ ����� (�������� � �.�.)
  void CreateList(long &list);//������� �������
};

#endif