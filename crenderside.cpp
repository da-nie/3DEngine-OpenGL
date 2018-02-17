#include "crenderside.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CRenderSide::CRenderSide(void)
{
 Location=0;
 Blend=false;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRenderSide::~CRenderSide(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::Draw(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting)
{
 long n;
 //подключим источники света
 glDisable(GL_LIGHT0);
 glDisable(GL_LIGHT1);
 glDisable(GL_LIGHT2);
 glDisable(GL_LIGHT3);
 glDisable(GL_LIGHT4);
 glDisable(GL_LIGHT5);
 glDisable(GL_LIGHT6);
 glDisable(GL_LIGHT7);
 for(n=0;n<LightingAmount;n++) cRenderLighting.SetGLLightingParameters(LightingArray[n],n);
 //установим параметры грани
 float m_emission[4]={Emission_R,Emission_G,Emission_B,1};
 glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,m_emission);
 if (Blend==true)
 {
  glDepthMask(GL_FALSE);
  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);
 }
 //выводим грань
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glTranslatef(TX,TY,TZ);
 glMatrixMode(GL_TEXTURE);
 glLoadIdentity();
 cRenderTextureFollow.SetTextureMatrix();
 cRenderTextureFollow.SetCurrentTexture(cRenderTexture);
 long size=vector_CRenderFragment.size();
 for(n=0;n<size;n++) vector_CRenderFragment[n].Draw();
 glMatrixMode(GL_MODELVIEW);
 glPopMatrix();
 if (Blend==true)
 {
  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
 }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::SetBlend(bool blend) 
{
 Blend=blend;
}
//----------------------------------------------------------------------------------------------------
//установить анимацию текстуры
//----------------------------------------------------------------------------------------------------
void CRenderSide::SetTextureFollow(CRenderTextureFollow cRenderTextureFollow_Set)
{
 cRenderTextureFollow=cRenderTextureFollow_Set;
}
//----------------------------------------------------------------------------------------------------
//установить положение
//----------------------------------------------------------------------------------------------------
void CRenderSide::SetLocation(long location)
{
 Location=location;
}
//----------------------------------------------------------------------------------------------------
//получить положение
//----------------------------------------------------------------------------------------------------
long CRenderSide::GetLocation(void)
{
 return(Location);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::Load(FILE *File) 
{
 long n;
 //нормаль
 N_X=LoadFloat(File);
 N_Y=LoadFloat(File);
 N_Z=LoadFloat(File);
 //источники света
 LightingAmount=LoadChar(File);
 for(n=0;n<LightingAmount;n++) LightingArray[n]=LoadLong(File);
 //эмиссия
 Emission_R=(float)((float)((unsigned char)LoadChar(File))/255.0);
 Emission_G=(float)((float)((unsigned char)LoadChar(File))/255.0);
 Emission_B=(float)((float)((unsigned char)LoadChar(File))/255.0);
 //фрагменты
 vector_CRenderFragment.clear();
 long amount=LoadLong(File);
 for(n=0;n<amount;n++)
 {
  CRenderFragment cRenderFragment;
  cRenderFragment.Load(File);
  cRenderFragment.SetNormal(N_X,N_Y,N_Z);
  vector_CRenderFragment.push_back(cRenderFragment);
 }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::Release(void)
{
 vector_CRenderFragment.clear();
 cRenderTextureFollow.Release();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::Translate(float VX,float VY,float VZ)
{
 TX=VX;
 TY=VY;
 TZ=VZ;
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::Processing(void)
{
 cRenderTextureFollow.Processing();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderSide::CreateList(long &list)
{
 long size=vector_CRenderFragment.size();
 for(long n=0;n<size;n++) vector_CRenderFragment[n].CreateList(list);
}
