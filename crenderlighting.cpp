#include "crenderlighting.h"

//----------------------------------------------------------------------------------------------------
//конструктор
CRenderLighting::CRenderLighting(void)
{
 vector_SLighting.clear();
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRenderLighting::~CRenderLighting(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderLighting::Release(void)
{
 vector_SLighting.clear();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderLighting::Load(FILE *File)
{
 Release();
 long amount=LoadLong(File); 
 for(long n=0;n<amount;n++)
 {
  SLighting sLighting;
  sLighting.X=LoadFloat(File);
  sLighting.Y=LoadFloat(File);
  sLighting.Z=LoadFloat(File);
  sLighting.R=(float)((float)((unsigned char)LoadChar(File))/255.0);
  sLighting.G=(float)(((float)(unsigned char)LoadChar(File))/255.0);
  sLighting.B=(float)((float)((unsigned char)LoadChar(File))/255.0);
  sLighting.Reserv_R=sLighting.R;
  sLighting.Reserv_G=sLighting.G;
  sLighting.Reserv_B=sLighting.B;
  sLighting.Mode=LoadLong(File);
  sLighting.TimeInterval=LoadLong(File);
  sLighting.Mode2_DarkTime=LoadFloat(File);
  sLighting.Mode2_LightTime=LoadFloat(File);
  sLighting.Mode2_MinimumLightLevel=LoadFloat(File);
  sLighting.Mode3_MinimumLightLevel=LoadFloat(File);
  sLighting.Mode3_CycleTime=LoadFloat(File);
  sLighting.Mode4_OnTime=LoadFloat(File);
  sLighting.Mode4_OffTime=LoadFloat(File);
  sLighting.Mode4_MinimumLightLevel=LoadFloat(File);
  sLighting.CurrentTime=0;
  sLighting.Brightness=(float)1;
  sLighting.DeltaBrightness=0;
  if (sLighting.Mode==3)
  {
   float dt=2*((float)sLighting.TimeInterval)*sLighting.Mode3_CycleTime;
   if (dt>0) sLighting.DeltaBrightness=(1-sLighting.Mode3_MinimumLightLevel)/dt;
  }
  vector_SLighting.push_back(sLighting);
 }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderLighting::SetGLLightingParameters(long index,long gllighting)
{
 if (vector_SLighting.size()<=index) return;
 float l_ambient[4]={0,0,0,1};
 float l_diffuse[4]={vector_SLighting[index].R,vector_SLighting[index].G,vector_SLighting[index].B,1};
 float l_specular[4]={0,0,0,1};
 float l_position[4]={vector_SLighting[index].X,vector_SLighting[index].Y,vector_SLighting[index].Z,1};
 glLightfv(GL_LIGHT0+gllighting,GL_AMBIENT,l_ambient);
 glLightfv(GL_LIGHT0+gllighting,GL_DIFFUSE,l_diffuse);
 glLightfv(GL_LIGHT0+gllighting,GL_POSITION,l_position);
 glLightfv(GL_LIGHT0+gllighting,GL_SPECULAR,l_specular);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderLighting::Processing(void)
{
 long amount=vector_SLighting.size();
 for(long n=0;n<amount;n++)
 {
  SLighting* sLightingPtr=&(vector_SLighting[n]);
  if (sLightingPtr->Mode==1) continue;//без изменений
  if (sLightingPtr->Mode==2)//случайное мигание
  {
   sLightingPtr->CurrentTime--;
   if (sLightingPtr->CurrentTime<=0)
   {
    if (sLightingPtr->Brightness==0)
    {
     sLightingPtr->CurrentTime=(long)(sLightingPtr->Mode2_LightTime*sLightingPtr->TimeInterval*rand()/RAND_MAX+1);
     sLightingPtr->R=sLightingPtr->Reserv_R;
     sLightingPtr->G=sLightingPtr->Reserv_G;
     sLightingPtr->B=sLightingPtr->Reserv_B;
     sLightingPtr->Brightness=1;
    }
    else
    {
     sLightingPtr->CurrentTime=(long)(sLightingPtr->Mode2_DarkTime*sLightingPtr->TimeInterval*rand()/RAND_MAX+1);
     sLightingPtr->R=sLightingPtr->Reserv_R*sLightingPtr->Mode2_MinimumLightLevel;
     sLightingPtr->G=sLightingPtr->Reserv_G*sLightingPtr->Mode2_MinimumLightLevel;
     sLightingPtr->B=sLightingPtr->Reserv_B*sLightingPtr->Mode2_MinimumLightLevel;
     sLightingPtr->Brightness=0;
    }
   }
  }
  if (sLightingPtr->Mode==3)//плавное изменение яркости
  {
   sLightingPtr->Brightness+=sLightingPtr->DeltaBrightness;
   if (sLightingPtr->Brightness<=sLightingPtr->Mode3_MinimumLightLevel)
   {
    sLightingPtr->Brightness=sLightingPtr->Mode3_MinimumLightLevel;
    sLightingPtr->DeltaBrightness=-sLightingPtr->DeltaBrightness;
   } 
   if (sLightingPtr->Brightness>=1)
   {
    sLightingPtr->Brightness=1;
    sLightingPtr->DeltaBrightness=-sLightingPtr->DeltaBrightness;
   } 
   sLightingPtr->R=sLightingPtr->Reserv_R*sLightingPtr->Brightness;
   sLightingPtr->G=sLightingPtr->Reserv_G*sLightingPtr->Brightness;
   sLightingPtr->B=sLightingPtr->Reserv_B*sLightingPtr->Brightness;
  }
  if (sLightingPtr->Mode==4)//мигание
  {
   if (sLightingPtr->CurrentTime>=sLightingPtr->TimeInterval*sLightingPtr->Mode4_OnTime && sLightingPtr->CurrentTime<=sLightingPtr->TimeInterval*sLightingPtr->Mode4_OffTime)
   {
    sLightingPtr->R=sLightingPtr->Reserv_R;
    sLightingPtr->G=sLightingPtr->Reserv_G;
    sLightingPtr->B=sLightingPtr->Reserv_B;
   }
   else
   {
    sLightingPtr->R=sLightingPtr->Reserv_R*sLightingPtr->Mode4_MinimumLightLevel;
    sLightingPtr->G=sLightingPtr->Reserv_G*sLightingPtr->Mode4_MinimumLightLevel;
    sLightingPtr->B=sLightingPtr->Reserv_B*sLightingPtr->Mode4_MinimumLightLevel;
   }
   sLightingPtr->CurrentTime++;
   if (sLightingPtr->CurrentTime>sLightingPtr->TimeInterval) sLightingPtr->CurrentTime=0;
  }
 }
}