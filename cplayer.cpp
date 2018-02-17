#include "cplayer.h"
 
extern CPhysicEngine cPhysicEngine;
 
//------------------------------------------------------------------------------
void CPlayer::LoadStartPos(char *FileName)
{
 FILE *File=fopen(FileName,"rb");
 x_start=0;
 y_start=0;
 anglexy_start=0;
 MoveOn=0;
 RotateOn=0;
 if (File==NULL) return;
 if (GetReadPos(File,"START POSITION")==1)
 { 
  x_start=LoadFloat(File);
  y_start=LoadFloat(File);
  anglexy_start=LoadFloat(File);
  MoveOn=0;
  RotateOn=0;
 }
 fclose(File);
}
void CPlayer::SetCharacterNumber(long ch)
{
 Character=ch;
 SCharacter sCharacter;
 sCharacter.X=x_start;
 sCharacter.Y=y_start;
 sCharacter.AngleXY=anglexy_start;
 sCharacter.Radius=16;
 sCharacter.Height=64;
 cPhysicEngine.SetCharacterParameters(Character,sCharacter);
 cPhysicEngine.SetCharacterCoordZAtDown(Character);
}
void CPlayer::RotateLeft(void)
{
 if (dAngleXY>0) dAngleXY=0;
 dAngleXY--;
 if (dAngleXY<-6) dAngleXY=-6;
 RotateOn=1;
}
void CPlayer::RotateRight(void)
{
 if (dAngleXY<0) dAngleXY=0;
 dAngleXY++;
 if (dAngleXY>6) dAngleXY=6;
 RotateOn=1;
}
void CPlayer::MoveUp(void)
{
 SCharacter sCharacter;
 cPhysicEngine.GetCharacterParameters(Character,&sCharacter);
 float anglexy=sCharacter.AngleXY;
 Dx=(float)(-sin(M_PI/180.0*anglexy));
 Dy=(float)(cos(M_PI/180.0*anglexy));
 MoveOn=1;
}
void CPlayer::MoveDown(void)
{
 SCharacter sCharacter;
 cPhysicEngine.GetCharacterParameters(Character,&sCharacter);
 float anglexy=sCharacter.AngleXY;
 Dx=(float)(sin(M_PI/180.0*anglexy));
 Dy=(float)(-cos(M_PI/180.0*anglexy));
 MoveOn=1;
}
void CPlayer::StepLeft(void)
{
 SCharacter sCharacter;
 cPhysicEngine.GetCharacterParameters(Character,&sCharacter);
 float anglexy=sCharacter.AngleXY;
 Dx=(float)(cos(M_PI/180.0*anglexy));
 Dy=(float)(sin(M_PI/180.0*anglexy));
 MoveOn=1;
}
void CPlayer::StepRight(void)
{
 SCharacter sCharacter;
 cPhysicEngine.GetCharacterParameters(Character,&sCharacter);
 float anglexy=sCharacter.AngleXY;
 Dx=(float)(-cos(M_PI/180.0*anglexy));
 Dy=(float)(-sin(M_PI/180.0*anglexy));
 MoveOn=1;
}
void CPlayer::SetLookParameter(float mdx,float mdy)
{
 if (mdx!=0)
 {
  dAngleXY=mdx;
  RotateOn=1;
 }
 cPhysicEngine.RotateCharacter(Character,0,-mdy);
}
void CPlayer::CenterViewZX(void)
{
 SCharacter sCharacter;
 cPhysicEngine.GetCharacterParameters(Character,&sCharacter);
 sCharacter.AngleZX=0;
 cPhysicEngine.SetCharacterParameters(Character,sCharacter);
}
void CPlayer::Processing(void)
{
 if (MoveOn==1)
 {
  cPhysicEngine.MoveCharacterXY(Character,Dx,Dy,10);
  MoveOn=0;
 }
 if (RotateOn==0) dAngleXY=0;
 RotateOn=0;
 cPhysicEngine.RotateCharacter(Character,dAngleXY,0);
}
void CPlayer::Activate(void)
{
 cPhysicEngine.Activate(Character);
}
void CPlayer::GetPlayerCharacter(SCharacter *sCharacter)
{
 cPhysicEngine.GetCharacterParameters(Character,sCharacter);
}
 
