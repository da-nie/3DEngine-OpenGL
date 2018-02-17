#ifndef CPLAYER_H
#define CPLAYER_H
 
#include "cphysicengine.h"
#include "formats.h"
 
class CPlayer
{
 protected:
  long Character;//����� ���������, ������� �������� �������
  float x_start,y_start,anglexy_start;//���������� ������
   
  float Dx,Dy;//������ ����������� ������
  long MoveOn;//1-����� ����������� ������
   
  float dAngleXY;//���������� ����
  long RotateOn;//1-����� ������������ ������
 public:
  //----------------------------------------------------------------------------
  void LoadStartPos(char *FileName);
  void SetCharacterNumber(long ch);//���������� ����� ���������-������
  void RotateLeft(void);
  void RotateRight(void);
  void MoveUp(void);
  void MoveDown(void);
  void StepLeft(void);
  void StepRight(void);
  void SetLookParameter(float mdx,float mdy);
  void CenterViewZX(void);
  void Processing(void);
  void Activate(void);
  void GetPlayerCharacter(SCharacter *sCharacter);
};
#endif
