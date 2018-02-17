#include "cphysicengine.h"
  
CPhysicEngine cPhysicEngine;

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CPhysicEngine::CPhysicEngine(void)
{
 vector_SCharacter.clear();
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CPhysicEngine::~CPhysicEngine(void)
{
 vector_SCharacter.clear();
}
//----------------------------------------------------------------------------------------------------
//добавить персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::SetCharacterInMap(long ch)
{
 vector_SCharacter.clear();
 for(long n=0;n<ch;n++)
 {
  SCharacter sCharacter;
  vector_SCharacter.push_back(sCharacter);
 }
}
//----------------------------------------------------------------------------------------------------
//удалить всех персонажей
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::DeleteAllCharacterInMap(void)
{
 vector_SCharacter.clear();
}
//----------------------------------------------------------------------------------------------------
//установить параметры персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::SetCharacterParameters(long ch,SCharacter sCharacter)
{
 vector_SCharacter[ch]=sCharacter;
 vector_SCharacter[ch].Rise=0;
}
//----------------------------------------------------------------------------------------------------
//установить координаты персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::SetCharacterCoord(long ch,float x,float y,float z,float anglexy)
{
 vector_SCharacter[ch].X=x;
 vector_SCharacter[ch].Y=y;
 vector_SCharacter[ch].Z=z;
 vector_SCharacter[ch].AngleXY=anglexy;
 vector_SCharacter[ch].Rise=0;
}
//----------------------------------------------------------------------------------------------------
//получить параметры персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::GetCharacterParameters(long ch,SCharacter *sCharacter)
{
 *sCharacter=vector_SCharacter[ch];
}
//----------------------------------------------------------------------------------------------------
//проверка столкновения с сегментом sgm
//----------------------------------------------------------------------------------------------------
long CPhysicEngine::OnCollision(long sgm,float x,float y,float z,float radius,float height,long *rise,float *maxz)
{
 long sx1;
 long sx2;
 long sy1;
 long sy2;
 vector_CSegmentPtr[sgm]->GetCoord(sx1,sy1,sx2,sy2);
 float xw1=sx1;
 float yw1=sy1;
 float xw2=sx2;
 float yw2=sy2;
 float xl1=xw1-x;
 float yl1=yw1-y;
 float xl2=xw2-x;
 float yl2=yw2-y;
 float a=xl2-xl1;
 float b=yl2-yl1;
 float kd=a*a+b*b;
 float ld=2*a*xl1+2*b*yl1;
 float md=xl1*xl1+yl1*yl1-radius*radius;
 float d=ld*ld-4*kd*md;
 if (d<0) return(0);
 float sd=(float)(sqrt(d));
 float l1=(-ld+sd)/(2*kd);
 float l2=(-ld-sd)/(2*kd);
 float xp1=xl1+l1*a;
 float yp1=yl1+l1*b;
 float xp2=xl1+l2*a;
 float yp2=yl1+l2*b;
 long impact=0;
 if (((xp1>=xl1 && xp1<=xl2) || (xp1>=xl2 && xp1<=xl1)) &&
 ((yp1>=yl1 && yp1<=yl2) || (yp1>=yl2 && yp1<=yl1))) impact=1;
 if (((xp2>=xl1 && xp2<=xl2) || (xp2>=xl2 && xp2<=xl1)) &&
 ((yp2>=yl1 && yp2<=yl2) || (yp2>=yl2 && yp2<=yl1))) impact=1;
 if (impact==0) return(0);
 if (vector_CSegmentPtr[sgm]->GetFrontier()==true)
 {
  impact=0;
  CSector *cSector_OnePtr=vector_CSegmentPtr[sgm]->GetCSectorOnePtr();
  CSector *cSector_TwoPtr=vector_CSegmentPtr[sgm]->GetCSectorTwoPtr();
  float up1=cSector_OnePtr->GetUpLevel();
  float down1=cSector_OnePtr->GetDownLevel();
  float up2=cSector_TwoPtr->GetUpLevel();
  float down2=cSector_TwoPtr->GetDownLevel();
  float fup1,fdown1;
  float fup2,fdown2;
  fup1=up1;
  fdown1=up2;
  fup2=down1;
  fdown2=down2;
  if (fup1<fdown1)
  {
   fup1=up2;
   fdown1=up1;
  }
  if (fup2<fdown2)
  {
   fup2=down2;
   fdown2=down1;
  }
  if (fup2>z-height+30) impact=1;
  if (fdown1<z) impact=1;
  if (fup2>z-height && fup2<z-height+30)
  {
   *maxz=fup2+height;
   *rise=1;
  }
 }
 if (impact!=0) 
 {
  *rise=0;	 
  return(1);
 }
 return(0);
}
//----------------------------------------------------------------------------------------------------
//изменение координаты Z персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::ChangeZCoord(long ch)
{
 float x=vector_SCharacter[ch].X;
 float y=vector_SCharacter[ch].Y;
 float z=vector_SCharacter[ch].Z;
 float Radius=vector_SCharacter[ch].Radius;
 float Height=vector_SCharacter[ch].Height;
 long Rise=vector_SCharacter[ch].Rise;
 float MaxZ=vector_SCharacter[ch].MaxZ;
 CSector *cSectorPtr=GetCSectorPtrForPoint(x,y);
 if (cSectorPtr==NULL) return;//игрок не в секторе
 float levelup=cSectorPtr->GetUpLevel();
 float leveldown=cSectorPtr->GetDownLevel();
 CSector *cSector_LevelUpPtr=cSectorPtr;
 CSector *cSector_LevelDownPtr=cSectorPtr;
 long size=vector_CSegmentPtr.size();
 for(long n=0;n<size;n++)
 {
  if (vector_CSegmentPtr[n]->GetFrontier()==false) continue;
  long sx1;
  long sx2;
  long sy1;
  long sy2;
  vector_CSegmentPtr[n]->GetCoord(sx1,sy1,sx2,sy2);
  float xw1=sx1;
  float yw1=sy1;
  float xw2=sx2;
  float yw2=sy2;
  float xl1=xw1-x;
  float yl1=yw1-y;
  float xl2=xw2-x;
  float yl2=yw2-y;
  float a=xl2-xl1;
  float b=yl2-yl1;
  float kd=a*a+b*b;
  float ld=2*a*xl1+2*b*yl1;
  float md=xl1*xl1+yl1*yl1-Radius*Radius;
  float d=ld*ld-4*kd*md;
  if (d<0) continue;
  float sd=(float)(sqrt(d));
  float l1=(-ld+sd)/(2*kd);
  float l2=(-ld-sd)/(2*kd);
  float xp1=xl1+l1*a;
  float yp1=yl1+l1*b;
  float xp2=xl1+l2*a;
  float yp2=yl1+l2*b;
  long impact=0;
  if (((xp1>=xl1 && xp1<=xl2) || (xp1>=xl2 && xp1<=xl1)) &&
  ((yp1>=yl1 && yp1<=yl2) || (yp1>=yl2 && yp1<=yl1))) impact=1;
  if (((xp2>=xl1 && xp2<=xl2) || (xp2>=xl2 && xp2<=xl1)) &&
  ((yp2>=yl1 && yp2<=yl2) || (yp2>=yl2 && yp2<=yl1))) impact=1;
  if (impact==0) continue;
  CSector* cSector_OnePtr=vector_CSegmentPtr[n]->GetCSectorOnePtr();
  CSector* cSector_TwoPtr=vector_CSegmentPtr[n]->GetCSectorTwoPtr();
  float up1=cSector_OnePtr->GetUpLevel();
  float down1=cSector_OnePtr->GetDownLevel();
  float up2=cSector_TwoPtr->GetUpLevel();
  float down2=cSector_TwoPtr->GetDownLevel();
  float floor_up,floor_down;
  float ceiling_up,ceiling_down;
  ceiling_up=up1;
  ceiling_down=up2;
  CSector *cSector_CeilingPtr=cSector_TwoPtr;
  floor_up=down1;
  floor_down=down2;
  CSector *cSector_FloorPtr=cSector_OnePtr;
  if (ceiling_up<ceiling_down)
  {
   ceiling_up=up2;
   ceiling_down=up1;
   cSector_CeilingPtr=cSector_OnePtr;
  }
  if (floor_up<floor_down)
  {
   floor_up=down2;
   floor_down=down1;
   cSector_FloorPtr=cSector_TwoPtr;
  }
  if (floor_up>leveldown)
  {
   leveldown=floor_up;
   cSector_LevelDownPtr=cSector_FloorPtr;
  }
  if (ceiling_down<levelup)
  {
   levelup=ceiling_down;
   cSector_LevelUpPtr=cSector_CeilingPtr;
  }
 }
 //теперь в levelup и leveldown-высоты пола и потолка в предельном случае
 if (Rise==0)
 {
  if (leveldown<z-Height)//персонаж падает
  {
   z-=(float)(9.8);
   if (leveldown>=z-Height) z=leveldown+Height;
  }
  if (leveldown>z-Height)//персонаж поднимает
  {
   z=leveldown+Height;
   if (z>=levelup-16)//голова упёрлась в потолок
   {
    TransferSectorMessage(cSectorPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
    TransferSectorMessage(cSector_LevelDownPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
    TransferSectorMessage(cSector_LevelUpPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
   }
  }
  if (levelup<z+16)//персонаж прижимает
  {
   z=levelup-16;
  }
 }
 else
 {
  z+=(float)(9.8);
  if (z>=MaxZ)//персонаж поднялся до запланированного уровня
  {
   z=MaxZ;
   Rise=0;
  }
  if (levelup<z+16)//персонаж прижимает
  {
   z=levelup-16;
   MaxZ=z;
   Rise=0;
  }
  if (leveldown>z-Height)//персонаж поднимает
  {
   z=leveldown+Height;
   if (z>=levelup-16)//голова упёрлась в потолок
   {
    TransferSectorMessage(cSectorPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
    TransferSectorMessage(cSector_LevelDownPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
    TransferSectorMessage(cSector_LevelUpPtr,PHE_HEAD_IMPACT_CEILING );//посылаем сообщение сектору о том, что голова упёрлась в потолок
   }
   MaxZ=z;
   Rise=0;
  }
 }
 vector_SCharacter[ch].Z=z;
 vector_SCharacter[ch].Rise=Rise;
 vector_SCharacter[ch].MaxZ=MaxZ;
}
//----------------------------------------------------------------------------------------------------
//перемещение персонажа
//----------------------------------------------------------------------------------------------------
long CPhysicEngine::MoveCharacterXY(long ch,float dx,float dy,long step)
{
 long n,m;
 float x=vector_SCharacter[ch].X;
 float y=vector_SCharacter[ch].Y;
 float z=vector_SCharacter[ch].Z;
 float Radius=vector_SCharacter[ch].Radius;
 float Height=vector_SCharacter[ch].Height;
 long Rise=vector_SCharacter[ch].Rise;
 float MaxZ=vector_SCharacter[ch].MaxZ;
 for(n=0;n<step;n++)
 {
  //посмотрим, какие сегменты мы пересекаем
  long size=vector_CSegmentPtr.size();
  vector_CollizionSegment.clear();
  for(m=0;m<size;m++)
  {
   long res=OnCollision(m,x+dx,y+dy,z,Radius,Height,&Rise,&MaxZ);
   if (res!=0) vector_CollizionSegment.push_back(m);
  }
  //столкновений не было
  if (vector_CollizionSegment.size()==0)
  {
   x=x+dx;
   y=y+dy;
   continue;
  }
  //теперь нам известны сегменты, с которыми мы столкнулись  
  //определим вектор по которому будет скользить персонаж
  float Dx=0;
  float Dy=0;
  long camount=vector_CollizionSegment.size();
  for(m=0;m<camount;m++)
  {
   long line=vector_CollizionSegment[m];
   long sx1;
   long sx2;
   long sy1;
   long sy2;
   vector_CSegmentPtr[line]->GetCoord(sx1,sy1,sx2,sy2);
   float xw1=sx1;
   float yw1=sy1;
   float xw2=sx2;
   float yw2=sy2;
   float vx=xw2-xw1;
   float vy=yw2-yw1;
   float ux=dx;
   float uy=dy;
   float normav=(float)(sqrt(vx*vx+vy*vy));
   float normau=(float)(sqrt(ux*ux+uy*uy));
   vx=vx/normav;
   vy=vy/normav;
   if (normau!=0)
   {
    ux=ux/normau;
    uy=uy/normau;
   }
   float cosa=ux*vx+uy*vy;
   float modul=(float)(fabs(cosa));
   if (cosa>0)
   {
    Dx=vx*modul;
    Dy=vy*modul;
   }
   else
   {
    Dx=-vx*modul;
    Dy=-vy*modul;
   }
   Dx=Dx/camount;
   Dy=Dy/camount;
   //проверим, нет ли столкновений при движении по такому вектору
   long size=vector_CSegmentPtr.size();
   for(long k=0;k<size;k++)
   {
    long res=OnCollision(k,x+Dx,y+Dy,z,Radius,Height,&Rise,&MaxZ);
    if (res!=0)
    {
     Dx=0;
     Dy=0;
     break;
    }  
   }
   x=x+Dx;
   y=y+Dy;
  }
 }
 vector_SCharacter[ch].X=x;
 vector_SCharacter[ch].Y=y;
 vector_SCharacter[ch].Z=z;
 vector_SCharacter[ch].Rise=Rise;
 vector_SCharacter[ch].MaxZ=MaxZ;
 //попробуем поменять координату z
 ChangeZCoord(ch);
 return(0);
}
//----------------------------------------------------------------------------------------------------
//вращение персонажа
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::RotateCharacter(long ch,float anglexy,float anglezx)
{
 float AngleXY=vector_SCharacter[ch].AngleXY;
 float AngleZX=vector_SCharacter[ch].AngleZX;
 AngleXY+=anglexy;
 AngleZX+=anglezx;
 if (AngleXY>=360) AngleXY-=360;
 if (AngleXY<0) AngleXY+=360;
 if (AngleZX>30) AngleZX=30;
 if (AngleZX<-30) AngleZX=-30;
  
 vector_SCharacter[ch].AngleXY=AngleXY;
 vector_SCharacter[ch].AngleZX=AngleZX;
}
//----------------------------------------------------------------------------------------------------
//поставить персонажа на пол
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::SetCharacterCoordZAtDown(long ch)
{
 float x=vector_SCharacter[ch].X;
 float y=vector_SCharacter[ch].Y;
 float height=vector_SCharacter[ch].Height;
 CSector *cSectorPtr=GetCSectorPtrForPoint(x,y); 
 if (cSectorPtr==NULL) return;
 vector_SCharacter[ch].Z=height+cSectorPtr->GetDownLevel();
}
//----------------------------------------------------------------------------------------------------
//персонаж активирует то что перед ним
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::Activate(long ch)
{
 float x=vector_SCharacter[ch].X;
 float y=vector_SCharacter[ch].Y;
 float z=vector_SCharacter[ch].Z;
 float Radius=vector_SCharacter[ch].Radius+50;
  
 CSector *cSectorPtr=GetCSectorPtrForPoint(x,y);
 if (cSectorPtr==NULL) return;
 long size=vector_CSegmentPtr.size();
 for(long n=0;n<size;n++)
 {
  if (vector_CSegmentPtr[n]->GetFrontier()==false) continue;
  long sx1;
  long sx2;
  long sy1;
  long sy2;
  vector_CSegmentPtr[n]->GetCoord(sx1,sy1,sx2,sy2);
  float xw1=sx1;
  float yw1=sy1;
  float xw2=sx2;
  float yw2=sy2;
  float xl1=xw1-x;
  float yl1=yw1-y;
  float xl2=xw2-x;
  float yl2=yw2-y;
  float a=xl2-xl1;
  float b=yl2-yl1;
  float kd=a*a+b*b;
  float ld=2*a*xl1+2*b*yl1;
  float md=xl1*xl1+yl1*yl1-Radius*Radius;
  float d=ld*ld-4*kd*md;
  if (d<0) continue;
  float sd=(float)(sqrt(d));
  float l1=(-ld+sd)/(2*kd);
  float l2=(-ld-sd)/(2*kd);
  float xp1=xl1+l1*a;
  float yp1=yl1+l1*b;
  float xp2=xl1+l2*a;
  float yp2=yl1+l2*b;
  long impact=0;
  if (((xp1>=xl1 && xp1<=xl2) || (xp1>=xl2 && xp1<=xl1)) &&
  ((yp1>=yl1 && yp1<=yl2) || (yp1>=yl2 && yp1<=yl1))) impact=1;
  if (((xp2>=xl1 && xp2<=xl2) || (xp2>=xl2 && xp2<=xl1)) &&
  ((yp2>=yl1 && yp2<=yl2) || (yp2>=yl2 && yp2<=yl1))) impact=1;
  if (impact==0) continue;
  CSector* cSector_OnePtr=vector_CSegmentPtr[n]->GetCSectorOnePtr();
  CSector* cSector_TwoPtr=vector_CSegmentPtr[n]->GetCSectorTwoPtr();
  TransferSectorMessage(cSector_OnePtr,PHE_ACTIVATE );//посылаем сообщение сектору о том, что его нужно активировать
  TransferSectorMessage(cSector_TwoPtr,PHE_ACTIVATE );//посылаем сообщение сектору о том, что его нужно активировать
 } 
}
//----------------------------------------------------------------------------------------------------
//цикл обработки персонажей
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::Processing(void)
{ 
 long size=vector_SCharacter.size();
 for(long n=0;n<size;n++) ChangeZCoord(n);
}
//----------------------------------------------------------------------------------------------------
//удалить все указатели на сектора
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::ClearAllSectorPtr(void)
{
 vector_CSectorPtr.clear();
}
//----------------------------------------------------------------------------------------------------
//добавить указатель на сектор
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::AddSectorPtr(CSector *cSectorPtr)
{
 vector_CSectorPtr.push_back(cSectorPtr); 
}
//----------------------------------------------------------------------------------------------------
//удалить все указатели на сегменты
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::ClearAllSegmentPtr(void)
{
 vector_CSegmentPtr.clear();
}
//----------------------------------------------------------------------------------------------------
//добавить указатель на сегмент
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::AddSegmentPtr(CSegment *cSegmentPtr)
{
 vector_CSegmentPtr.push_back(cSegmentPtr); 
}
//----------------------------------------------------------------------------------------------------
//получить указатель на сектор по координатам точки
//----------------------------------------------------------------------------------------------------
CSector* CPhysicEngine::GetCSectorPtrForPoint(float x,float y)
{
 long size=vector_CSectorPtr.size();
 for(long n=0;n<size;n++)
 {
  if (vector_CSectorPtr[n]->CheckPointInSector(x,y)==true) return(vector_CSectorPtr[n]);
 }
 return(NULL);
}
//----------------------------------------------------------------------------------------------------
//получить указатель на сектор по его номеру и типу
//----------------------------------------------------------------------------------------------------
CSector* CPhysicEngine::GetCSectorPtrForIndexAndType(long index,long type)
{
 long size=vector_CSectorPtr.size();
 for(long n=0;n<size;n++)
 {
  if (vector_CSectorPtr[n]->GetSectorType()==type && vector_CSectorPtr[n]->GetSectorIndex()==index) return(vector_CSectorPtr[n]);
 }
 return(NULL);
}
//----------------------------------------------------------------------------------------------------
//получить указатель на сектор по его номеру
//----------------------------------------------------------------------------------------------------
CSector* CPhysicEngine::GetCSectorPtrForIndex(long index)
{
 long size=vector_CSectorPtr.size();
 if (size<=index) return(NULL);
 return(vector_CSectorPtr[index]);
}
//----------------------------------------------------------------------------------------------------
//послать сектору сообщение
//----------------------------------------------------------------------------------------------------
void CPhysicEngine::TransferSectorMessage(CSector *cSectorPtr,long message)
{ 
 long sector_type=cSectorPtr->GetSectorType();
 if (message==PHE_HEAD_IMPACT_CEILING)
 {
  if (sector_type==SECTOR_TYPE_SIMPLY_DOOR)//посылаем это сообщение обычной двери
  {
   (reinterpret_cast<CSimplyDoor*>(cSectorPtr))->Message_HeadImpactCeiling();
   return;
  }
 }
 if (message==PHE_ACTIVATE)
 {
  if (sector_type==SECTOR_TYPE_SIMPLY_DOOR)//посылаем это сообщение обычной двери
  {
   (reinterpret_cast<CSimplyDoor*>(cSectorPtr))->Message_HeadImpactCeiling();
   return;
  }
 }
}
