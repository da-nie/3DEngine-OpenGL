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

//��������� ��������
struct SPortalComponent
{
 CSector *cSectorPtr;//��������� �� ������
 float X,Y;//���������� �����(��� ����� ��� ���� ������)
 //������ ������ ��������� ����� ���� ���������
 float VL1_X,VL1_Y;//������������ ������
 //������ ������ ���������
 float VL2_X,VL2_Y;//������������ ������
  
 //������ ������ ���������
 float L1_X,L1_Y;//������������ ������
 //������ ������ ���������
 float L2_X,L2_Y;//������������ ������
 //������ ����������� ������� ���������
 float X1,Y1;
 float X2,Y2;
};

//��������� ������
struct SFogSetting
{
 float R;
 float G;
 float B;
 float Density;
 long Enable;
};
 
 
#endif
