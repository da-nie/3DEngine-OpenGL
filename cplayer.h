#ifndef CPLAYER_H
#define CPLAYER_H
 
#include "cphysicengine.h"
#include "formats.h"
 
class CPlayer
{
 protected:
  long Character;//номер персонажа, который является игроком
  float x_start,y_start,anglexy_start;//координаты старта
   
  float Dx,Dy;//вектор перемещения игрока
  long MoveOn;//1-нужно передвигать игрока
   
  float dAngleXY;//приращение угла
  long RotateOn;//1-нужно поворачивать игрока
 public:
  //----------------------------------------------------------------------------
  void LoadStartPos(char *FileName);
  void SetCharacterNumber(long ch);//установить номер персонажа-игрока
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
