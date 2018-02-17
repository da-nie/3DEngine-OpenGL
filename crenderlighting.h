#ifndef CRENDER_LIGHTING_H
#define CRENDER_LIGHTING_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include "formats.h"

#include <vector>
using namespace std;

//����� ���������� ����� 
class CRenderLighting
{
 protected:
  struct SLighting
  {
   //����������
   float X;
   float Y;
   float Z;
   //����
   float R;
   float G;
   float B;   
   long Mode;//����� ������
   long TimeInterval;//�������� ������� ������ ��������� (�� �� �������� ��������)
   float Mode2_DarkTime;
   float Mode2_LightTime;
   float Mode2_MinimumLightLevel;
   float Mode3_MinimumLightLevel;
   float Mode3_CycleTime;
   float Mode4_OnTime;
   float Mode4_OffTime;
   float Mode4_MinimumLightLevel;
   //��������� ������
   float Reserv_R;
   float Reserv_G;
   float Reserv_B;
   //������� ������
   float Brightness;
   float DeltaBrightness;
   long CurrentTime;//������� ����� �� ���������
  };
  vector<SLighting> vector_SLighting;//��������� �����
 public:
  CRenderLighting(void);//�����������
  ~CRenderLighting(void);//����������
 public:
  void Release(void);//������� ��������� �����
  void Load(FILE *File);//��������� ��������� �����
  void SetGLLightingParameters(long index,long gllighting);//���������� ��������� ��������� OpenGL � ��������� ��������� index
  void Processing(void);//���������� �������� ���������� �����
};
#endif
