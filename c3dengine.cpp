#include "c3dengine.h"
 
extern CPhysicEngine cPhysicEngine;

extern double Lighting_Constant_Attenuation;
extern double Lighting_Linear_Attenuation;
extern double Lighting_Quadric_Attenuation;
extern float Lighting_Ambient_R;
extern float Lighting_Ambient_G;
extern float Lighting_Ambient_B;
extern long List;

//------------------------------------------------------------------------------
C3DEngine::C3DEngine(void)
{
 cPhysicEngine.ClearAllSegmentPtr();
 cPhysicEngine.ClearAllSectorPtr();
 cRenderLighting.Release();
}
void C3DEngine::LoadSegment(char *FileName)
{
 vector_CSegment.clear();
 FILE *File=fopen(FileName,"rb");
 if (File==NULL) return;
 if (GetReadPos(File,"SEGMENTS STRUCTURE")==1)
 {
  long amount=LoadLong(File);
  for(long n=0;n<amount;n++)
  {
   CSegment cSegment;
   cSegment.Load(File,cRenderTexture,n);
   vector_CSegment.push_back(cSegment);
  }
 }
 fclose(File);
}
void C3DEngine::LoadSimplySector(char *FileName)
{
 vector_CSimplySector.clear();
 FILE *File=fopen(FileName,"rb");
 if (File==NULL) return;
 if (GetReadPos(File,"SIMPLYSECTORS STRUCTURE")==1)
 {
  long amount=LoadLong(File);
  for(long n=0;n<amount;n++)
  {
   CSimplySector cSimplySector;
   cSimplySector.Load(File,cRenderTexture,n);
   vector_CSimplySector.push_back(cSimplySector);
  }
 }
 fclose(File);
}
void C3DEngine::LoadSimplyDoor(char *FileName)
{
 vector_CSimplyDoor.clear();
 FILE *File=fopen(FileName,"rb");
 if (File==NULL) return;
 if (GetReadPos(File,"SIMPLYDOORS STRUCTURE")==1)
 {
  long amount=LoadLong(File);
  for(long n=0;n<amount;n++)
  {
   CSimplyDoor cSimplyDoor;
   cSimplyDoor.Load(File,cRenderTexture,n);
   vector_CSimplyDoor.push_back(cSimplyDoor);
  }
 }
 fclose(File);
}

void C3DEngine::LoadTexture(char *FileName)
{ 
 cRenderTexture.LoadAndBuildGLTexture(FileName);
}
void C3DEngine::LoadStage(char *FileName)
{
 glEnable(GL_TEXTURE_2D);
 List=1;
 //загружаем параметры освещения
 LoadLighting(FileName);
 for(long n=0;n<8;n++)
 {
  glLightf(GL_LIGHT0+n,GL_CONSTANT_ATTENUATION,(float)Lighting_Constant_Attenuation);
  glLightf(GL_LIGHT0+n,GL_LINEAR_ATTENUATION,(float)Lighting_Linear_Attenuation);
  glLightf(GL_LIGHT0+n,GL_QUADRATIC_ATTENUATION,(float)Lighting_Quadric_Attenuation);
 }
 //загружаем сегменты
 LoadSegment(FileName);
 //работа с секторами
 //загружаем сектора
 LoadSimplySector(FileName);
 LoadSimplyDoor(FileName);
 //заполняем структуру
 SetSurround(); 
 //загружаем текстуры
 LoadTexture("texture.pak");
 DefinitionSegmentAndPortal(); 
 //загружаем параметры тумана
 LoadFogParameters(FileName);
}
void C3DEngine::LoadFogParameters(char *FileName)
{
 FILE *File=fopen(FileName,"rb");
 if (File==NULL) return;
 if (GetReadPos(File,"GLOBAL FOG STRUCTURE")==1)
 {
  sFogSetting.R=LoadFloat(File);
  sFogSetting.G=LoadFloat(File);
  sFogSetting.B=LoadFloat(File);
  sFogSetting.Density=LoadFloat(File);
  sFogSetting.Enable=(unsigned char)LoadChar(File);
  float fogcolor[4];
  fogcolor[0]=sFogSetting.R;
  fogcolor[1]=sFogSetting.G;
  fogcolor[2]=sFogSetting.B;
  fogcolor[3]=1;
  if (sFogSetting.Enable==1)
  {
   glEnable(GL_FOG);
   glFogf(GL_FOG_MODE,GL_EXP);
   glFogfv(GL_FOG_COLOR,fogcolor);
   glFogf(GL_FOG_DENSITY,sFogSetting.Density);
   glHint(GL_FOG_HINT,GL_FASTEST);
  }
  else glDisable(GL_FOG);
 }
 fclose(File);
}
void C3DEngine::LoadLighting(char *FileName)
{
 cRenderLighting.Release();
 FILE *File=fopen(FileName,"rb");
 if (File==NULL) return;
 if (GetReadPos(File,"LIGHTINGS STRUCTURE")==1)
 {
  cRenderLighting.Load(File);

  Lighting_Constant_Attenuation=LoadFloat(File);
  Lighting_Linear_Attenuation=LoadFloat(File);
  Lighting_Quadric_Attenuation=LoadFloat(File);
  Lighting_Ambient_R=(float)((float)((unsigned char)LoadChar(File))/255.0);
  Lighting_Ambient_G=(float)((float)((unsigned char)LoadChar(File))/255.0);
  Lighting_Ambient_B=(float)((float)((unsigned char)LoadChar(File))/255.0);
 }
 fclose(File);
}
void C3DEngine::SetSurround(void)
{
 //добавляем сектора
 long n;
 //работа с секторами
 cPhysicEngine.ClearAllSectorPtr();
 long ssamount=vector_CSimplySector.size();
 for(n=0;n<ssamount;n++)
 {
  cPhysicEngine.AddSectorPtr(dynamic_cast<CSector*>(&vector_CSimplySector[n]));
  vector_CSimplySector[n].ClearSegmentList();
  vector_CSimplySector[n].ClearPortalList();
 }
 long sdamount=vector_CSimplyDoor.size();
 for(n=0;n<sdamount;n++)
 {
  cPhysicEngine.AddSectorPtr(dynamic_cast<CSector*>(&vector_CSimplyDoor[n]));
  vector_CSimplyDoor[n].ClearSegmentList();
  vector_CSimplyDoor[n].ClearPortalList();
 }
 //добавляем сегменты
 cPhysicEngine.ClearAllSegmentPtr();
 long samount=vector_CSegment.size();
 for(n=0;n<samount;n++)
 {
  //определим для сегментов их сектора
  if (vector_CSegment[n].GetFrontier()==false)
  {
   vector_CSegment[n].SetCSectorOnePtr(cPhysicEngine.GetCSectorPtrForIndexAndType(vector_CSegment[n].GetSectorOne(),vector_CSegment[n].GetSectorOneType()));
   vector_CSegment[n].SetCSectorTwoPtr(cPhysicEngine.GetCSectorPtrForIndexAndType(vector_CSegment[n].GetSectorOne(),vector_CSegment[n].GetSectorOneType()));
  }
  else
  {
   vector_CSegment[n].SetCSectorOnePtr(cPhysicEngine.GetCSectorPtrForIndexAndType(vector_CSegment[n].GetSectorOne(),vector_CSegment[n].GetSectorOneType()));
   vector_CSegment[n].SetCSectorTwoPtr(cPhysicEngine.GetCSectorPtrForIndexAndType(vector_CSegment[n].GetSectorTwo(),vector_CSegment[n].GetSectorTwoType()));
  }
  cPhysicEngine.AddSegmentPtr(&(vector_CSegment[n]));
 }
}
void C3DEngine::DefinitionSegmentAndPortal(void)
{	
 long m;
 long sector_index=0;
 while(1)
 {
  CSector *cSectorPtr=cPhysicEngine.GetCSectorPtrForIndex(sector_index);
  if (cSectorPtr==NULL) break;  
  //определяем, каким секторам какие сегменты и порталы соответствуют
  cSectorPtr->ClearSegmentList();
  cSectorPtr->ClearPortalList();
  cSectorPtr->ClearEnabledPortalList();

  long sector=cSectorPtr->GetSectorIndex();
  long type=cSectorPtr->GetSectorType();
  long size=vector_CSegment.size();
  for(m=0;m<size;m++)
  {
   if (vector_CSegment[m].GetFrontier()==false)
   {
    if (vector_CSegment[m].GetSectorOne()==sector && vector_CSegment[m].GetSectorOneType()==type) cSectorPtr->AddSegmentIndex(m);
   }
   else
   {
    if (vector_CSegment[m].GetSectorOne()==sector && vector_CSegment[m].GetSectorOneType()==type)
    {
     cSectorPtr->AddPortalIndex(m);
     cSectorPtr->AddEnabledPortalIndex(0);
    }
    if (vector_CSegment[m].GetSectorTwo()==sector && vector_CSegment[m].GetSectorTwoType()==type)
    {
     cSectorPtr->AddPortalIndex(m);
     cSectorPtr->AddEnabledPortalIndex(0);
    }
   }
  }
  sector_index++;
 }
}
void C3DEngine::DrawBlendSegment(void)
{
 glDepthMask(GL_FALSE);
 glDisable(GL_CULL_FACE);
 long size=vector_CSegment.size();
 for(long n=0;n<size;n++)
 {
  vector_CSegment[n].DrawBlendSegment(cRenderTexture,cRenderLighting);
 }
 glEnable(GL_CULL_FACE);
 glDepthMask(GL_TRUE);
}

void C3DEngine::DrawStage(SPortalComponent pc,SCharacter *sCharacter)
{
 CSector *cSectorPtr=pc.cSectorPtr;
 if (cSectorPtr==NULL) return;
 //выведем все сегменты и порталы сектора
 long segment_index=0;
 while(1)
 {
  long segment=cSectorPtr->GetSegmentIndex(segment_index);
  if (segment<0) break;
  segment_index++;
  if (vector_CSegment[segment].GetUse()==true) continue;
  long sx1;
  long sy1;
  long sx2;
  long sy2;
  vector_CSegment[segment].GetCoord(sx1,sy1,sx2,sy2);
  float x1=sx1;
  float y1=sy1;
  float x2=sx2;
  float y2=sy2;
  float xo,yo;
  long v1=GetPosition(x1,y1,pc.X1,pc.Y1,pc.X2,pc.Y2);
  long v2=GetPosition(x2,y2,pc.X1,pc.Y1,pc.X2,pc.Y2);
  if (v1<0 && v2<0) continue;//сегмент не видим
  if (v1<0)
  {
   Intersection(pc.X1,pc.Y1,pc.X2,pc.Y2,x1,y1,x2,y2,&xo,&yo);
   x1=xo;
   y1=yo;
  }
  if (v2<0)
  {
   Intersection(pc.X1,pc.Y1,pc.X2,pc.Y2,x1,y1,x2,y2,&xo,&yo);
   x2=xo;
   y2=yo;
  }
  long p1_l1=GetPosition(x1,y1,pc.X,pc.Y,pc.X+pc.VL1_X,pc.Y+pc.VL1_Y);
  long p2_l1=GetPosition(x2,y2,pc.X,pc.Y,pc.X+pc.VL1_X,pc.Y+pc.VL1_Y);
  long p1_l2=GetPosition(x1,y1,pc.X,pc.Y,pc.X+pc.VL2_X,pc.Y+pc.VL2_Y);
  long p2_l2=GetPosition(x2,y2,pc.X,pc.Y,pc.X+pc.VL2_X,pc.Y+pc.VL2_Y);
  if (p1_l1<0 && p2_l1<0 && p1_l2<0 && p2_l2<0) continue;
  if (p1_l1>0 && p2_l1>0 && p1_l2>0 && p2_l2>0) continue;
  vector_CSegment[segment].DrawSegment(cRenderTexture,cRenderLighting);  
 } 
 //выведем порталы
 long portal_index=0;
 while(1)
 {
  long portal=cSectorPtr->GetPortalIndex(portal_index);
  if (portal<0) break;
  portal_index++;
  if (vector_CSegment[portal].GetUse()==true) continue;
  vector_CSegment[portal].DrawSegment(cRenderTexture,cRenderLighting);
 }
 //работа с секторами
 //выводим сектора
 if (cSectorPtr->GetSectorType()==SECTOR_TYPE_SIMPLY_SECTOR) (reinterpret_cast<CSimplySector*>(cSectorPtr))->DrawSector(sCharacter->Z,cRenderTexture,cRenderLighting);
 if (cSectorPtr->GetSectorType()==SECTOR_TYPE_SIMPLY_DOOR) (reinterpret_cast<CSimplyDoor*>(cSectorPtr))->DrawSector(sCharacter->Z,cRenderTexture,cRenderLighting); 
 //работа с секторами
 //вызываем для всех порталов эту же функцию
 //создаём список свободных порталов сектора
 portal_index=0;
 cSectorPtr->ClearEnabledPortalList();
 while(1)
 {
  long portal=cSectorPtr->GetPortalIndex(portal_index);
  if (portal<0) break;
  portal_index++;
  if (vector_CSegment[portal].GetPortalDisableState()==true) continue;
  cSectorPtr->AddEnabledPortalIndex(portal);
  //блокируем портал
  vector_CSegment[portal].SetPortalDisableState(true);
 }
 portal_index=0;
 while(1)
 {
  long portal=cSectorPtr->GetEnabledPortalIndex(portal_index);
  if (portal<0) break;
  portal_index++;
  SPortalComponent pcnew=pc;
  CSector *cSector_OnePtr=vector_CSegment[portal].GetCSectorOnePtr();
  CSector *cSector_TwoPtr=vector_CSegment[portal].GetCSectorTwoPtr();
  long sx1;
  long sy1;
  long sx2;
  long sy2;
  vector_CSegment[portal].GetCoord(sx1,sy1,sx2,sy2);
  float x1=sx1;
  float y1=sy1;
  float x2=sx2;
  float y2=sy2;

  //проверим, не стоим ли мы на портале (т.к. возможна ошибка округления и значит глюки)
  //если мы стоим на портале, то ничего не меняется !!!
  long v=GetPosition(sCharacter->X,sCharacter->Y,x1,y1,x2,y2);
  if (v==0)//мы стоим на портале
  {
   if (cSector_OnePtr!=cSectorPtr)
   {
    pcnew.cSectorPtr=cSector_OnePtr;
    DrawStage(pcnew,sCharacter);
   }
   if (cSector_TwoPtr!=cSectorPtr)
   {
    pcnew.cSectorPtr=cSector_TwoPtr;
    DrawStage(pcnew,sCharacter);
   }
   continue;
  }
  //отсечём по границе линии обзора
  float xo,yo;
  long v1=GetPosition(x1,y1,pc.X1,pc.Y1,pc.X2,pc.Y2);
  long v2=GetPosition(x2,y2,pc.X1,pc.Y1,pc.X2,pc.Y2);
  if (v1<0 && v2<0) continue;//портал не видим
  if (v1<0)
  {
   Intersection(pc.X1,pc.Y1,pc.X2,pc.Y2,x1,y1,x2,y2,&xo,&yo);
   x1=xo;
   y1=yo;
  }
  if (v2<0)
  {
   Intersection(pc.X1,pc.Y1,pc.X2,pc.Y2,x1,y1,x2,y2,&xo,&yo);
   x2=xo;
   y2=yo;
  }
  //проверим видимость портала
  long p1_l1=GetPosition(x1,y1,pc.X,pc.Y,pc.X+pc.L1_X,pc.Y+pc.L1_Y);
  long p2_l1=GetPosition(x2,y2,pc.X,pc.Y,pc.X+pc.L1_X,pc.Y+pc.L1_Y);
  long p1_l2=GetPosition(x1,y1,pc.X,pc.Y,pc.X+pc.L2_X,pc.Y+pc.L2_Y);
  long p2_l2=GetPosition(x2,y2,pc.X,pc.Y,pc.X+pc.L2_X,pc.Y+pc.L2_Y);
  if (p1_l1<=0 && p2_l1<=0 && p1_l2<=0 && p2_l2<=0) continue;
  if (p1_l1>=0 && p2_l1>=0 && p1_l2>=0 && p2_l2>=0) continue;
  //вычисляем новые прямые отсечения
  if (p1_l1<0 && p2_l1>0 || p1_l1<0 && p2_l1==0 ||
  p1_l1>0 && p2_l1<0 || p1_l1>0 && p2_l1==0)
  {
   if (p1_l1<=0)
   {
    if (p1_l2>=0)
    {
     pcnew.L2_X=x1-pc.X;
     pcnew.L2_Y=y1-pc.Y;
    }
   }
   else
   {
    if (p2_l2>=0)
    {
     pcnew.L2_X=x2-pc.X;
     pcnew.L2_Y=y2-pc.Y;
    }
   }
  }
  if (p1_l2<0 && p2_l2>0 || p1_l2<0 && p2_l2==0 ||
  p1_l2>0 && p2_l2<0 || p1_l2>0 && p2_l2==0)
  {
   if (p1_l2>=0)
   {
    if (p1_l1<=0)
    {
     pcnew.L1_X=x1-pc.X;
     pcnew.L1_Y=y1-pc.Y;
    }
   }
   else
   {
    if (p2_l1<=0)
    {
     pcnew.L1_X=x2-pc.X;
     pcnew.L1_Y=y2-pc.Y;
    }
   }
  }
  if (p1_l1<=0 && p2_l1<=0 && p1_l2>=0 && p2_l2>=0 && !(p1_l1==0 && p2_l2==0))
  {
   pcnew.L1_X=x1-pc.X;
   pcnew.L1_Y=y1-pc.Y;
   pcnew.L2_X=x2-pc.X;
   pcnew.L2_Y=y2-pc.Y;
   //считаем скалярное произведение, тот вектор, у которого оно больше-ближайший к старой линии
   float n1=(float)(sqrt(pcnew.L1_X*pcnew.L1_X+pcnew.L1_Y*pcnew.L1_Y));
   float n2=(float)(sqrt(pcnew.L2_X*pcnew.L2_X+pcnew.L2_Y*pcnew.L2_Y));
   float n3=(float)(sqrt(pc.L1_X*pc.L1_X+pc.L1_Y*pc.L1_Y));
   float sc1=(pcnew.L1_X*pc.L1_X+pcnew.L1_Y*pc.L1_Y)/(n1*n3);
   float sc2=(pcnew.L2_X*pc.L1_X+pcnew.L2_Y*pc.L1_Y)/(n2*n3);
   if (sc1<sc2)//нужно обменять вектора
   {
    pcnew.L1_X=x2-pc.X;
    pcnew.L1_Y=y2-pc.Y;
    pcnew.L2_X=x1-pc.X;
    pcnew.L2_Y=y1-pc.Y;
   }
  }
  if (cSector_OnePtr!=cSectorPtr)
  {
   pcnew.cSectorPtr=cSector_OnePtr;
   DrawStage(pcnew,sCharacter);
  }
  if (cSector_TwoPtr!=cSectorPtr)
  {
   pcnew.cSectorPtr=cSector_TwoPtr;
   DrawStage(pcnew,sCharacter);
  }
 }
 //разблокируем порталы
 portal_index=0;
 while(1)
 {
  long portal=cSectorPtr->GetEnabledPortalIndex(portal_index);
  if (portal<0) break;
  vector_CSegment[portal].SetPortalDisableState(false);
  portal_index++;
 }
 return;
}
void C3DEngine::Draw(SCharacter *sCharacter)
{
 long n;
 //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
 if (sFogSetting.Enable==1) glClearColor(sFogSetting.R,sFogSetting.G,sFogSetting.B,1);
 else glClearColor(0,0,0,0);
 glClearColor(0,0,0,0);
 glClear(GL_DEPTH_BUFFER_BIT);
 glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
 //работа с секторами
 long size;
 size=vector_CSimplySector.size();
 for(n=0;n<size;n++) vector_CSimplySector[n].SetState();
 size=vector_CSimplyDoor.size();
 for(n=0;n<size;n++) vector_CSimplyDoor[n].SetState();
 //работа с секторами
 size=vector_CSegment.size();
 for(n=0;n<size;n++) vector_CSegment[n].InitState();
 SPortalComponent pc;
 pc.cSectorPtr=cPhysicEngine.GetCSectorPtrForPoint(sCharacter->X,sCharacter->Y);
 pc.X=sCharacter->X;
 pc.Y=sCharacter->Y;
 pc.L1_X=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY-50)));
 pc.L1_Y=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY-50)));
 pc.L2_X=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY+50)));
 pc.L2_Y=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY+50)));
 pc.VL1_X=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY-50)));
 pc.VL1_Y=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY-50)));
 pc.VL2_X=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY+50)));
 pc.VL2_Y=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY+50)));
 pc.X1=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY-90))+sCharacter->X);
 pc.Y1=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY-90))+sCharacter->Y);
 pc.X2=(float)(10000.0*sin(M_PI/180*(-sCharacter->AngleXY+90))+sCharacter->X);
 pc.Y2=(float)(10000.0*cos(M_PI/180*(-sCharacter->AngleXY+90))+sCharacter->Y);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glRotatef(sCharacter->AngleZX,1,0,0);
 glRotatef(sCharacter->AngleXY,0,1,0);
 glTranslatef(sCharacter->X,-sCharacter->Z,sCharacter->Y);
 /* glGetIntegerv(GL_VIEWPORT,viewport);
 glGetDoublev(GL_MODELVIEW_MATRIX,(GLdouble*)mvm);
 glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
 glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);*/
 glMatrixMode(GL_TEXTURE);
 if (pc.cSectorPtr!=NULL) DrawStage(pc,sCharacter);
 float mb_ambient[]={1,1,1,0.15f};
 float mb_diffuse[]={1,1,1,0.15f};
 float mb_specular[]={1,1,1,0.15f};
 float mb_emission[]={0,0,0,0.15f};
 float mb_shininess[]={100};
 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mb_ambient);
 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mb_diffuse);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mb_specular);
 glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mb_emission);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mb_shininess);
 // glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
 glEnable(GL_BLEND);
 DrawBlendSegment();
 glDisable(GL_BLEND);
 glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
 float m_ambient[]={1,1,1,1};
 float m_diffuse[]={1,1,1,1};
 float m_specular[]={1,1,1,1};
 float m_emission[]={0,0,0,1};
 float m_shininess[]={100};
 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_ambient);
 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_diffuse);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_specular);
 glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,m_emission);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,m_shininess);
 glFlush();
}
void C3DEngine::Animate(long Tick)
{
 long n;
 long size;
 //работа с секторами
 size=vector_CSimplySector.size();
 for(n=0;n<size;n++) vector_CSimplySector[n].Animate(Tick%2);
 size=vector_CSimplyDoor.size();
 for(n=0;n<size;n++) vector_CSimplyDoor[n].Animate(Tick%2);
 //работа с сегментами
 size=vector_CSegment.size();
 for(n=0;n<size;n++) vector_CSegment[n].Animate(Tick%2);
 AnimateLighting();
}
void C3DEngine::AnimateScroll(void)
{
 long n;
 long size;
 //работа с секторами
 size=vector_CSimplySector.size();
 for(n=0;n<size;n++) vector_CSimplySector[n].AnimateScroll();
 size=vector_CSimplyDoor.size();
 for(n=0;n<size;n++) vector_CSimplyDoor[n].AnimateScroll();
 //работа с сегментами
 size=vector_CSegment.size();
 for(n=0;n<size;n++) vector_CSegment[n].AnimateScroll();
}
void C3DEngine::AnimateLighting(void)
{
 cRenderLighting.Processing();
}
void C3DEngine::DeleteStage(void)
{
 cRenderLighting.Release();
 //работа с секторами
 vector_CSimplySector.clear();
 vector_CSimplyDoor.clear();
 //работа с сегментами
 vector_CSegment.clear();
 cPhysicEngine.DeleteAllCharacterInMap();
 cPhysicEngine.ClearAllSectorPtr();
 cPhysicEngine.ClearAllSegmentPtr();
 cRenderTexture.Release();
}
