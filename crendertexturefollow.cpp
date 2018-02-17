#include "crendertexturefollow.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CRenderTextureFollow::CRenderTextureFollow(void)
{
 CurrentPointer=0;
 dPointer=0;
 vector_TextureIndexFollow.clear();
 SpeedLToR=0;
 SpeedUToD=0;
 Dx=0;
 Dy=0;
 Mode=0;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRenderTextureFollow::~CRenderTextureFollow(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//загрузить анимацию текстуры
//----------------------------------------------------------------------------------------------------
void CRenderTextureFollow::Load(FILE *File,CRenderTexture &cRenderTexture)
{
 Mode=LoadLong(File);
 long amount=LoadLong(File);
 for(long n=0;n<amount;n++)
 {
  long index=cRenderTexture.AddEnabledTextureIndex(LoadLong(File));
  vector_TextureIndexFollow.push_back(index);
 }
 ScrollLToR=LoadLong(File);
 SpeedLToR=LoadLong(File);
 ScrollUToD=LoadLong(File);
 SpeedUToD=LoadLong(File);
 CurrentPointer=0;
 dPointer=1;
 Dx=0;
 Dy=0;
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderTextureFollow::Release(void)
{
 vector_TextureIndexFollow.clear();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderTextureFollow::SetTextureMatrix(void)
{
 glTranslatef((float)(-(float)Dy/128.0f),(float)(-(float)Dx/128.0f),0);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderTextureFollow::SetCurrentTexture(CRenderTexture &cRenderTexture)
{
 if (vector_TextureIndexFollow.size()<=CurrentPointer) return;
 cRenderTexture.SelectTexture(vector_TextureIndexFollow[CurrentPointer]);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderTextureFollow::Processing(void)
{
 //анимация смены текстуры
 if (Mode!=0)
 {
  CurrentPointer+=dPointer;
  if (Mode==1)
  {
   if (CurrentPointer>=vector_TextureIndexFollow.size()) CurrentPointer=0;
  }
  if (Mode==2)
  {
   if (CurrentPointer>=vector_TextureIndexFollow.size())
   {
    CurrentPointer=vector_TextureIndexFollow.size()-1;
    dPointer=-dPointer;
   }
   if (CurrentPointer<=0)
   {
    CurrentPointer=0;
    dPointer=-dPointer;
   }
  }
 }
 //анимация перемещения текстуры (скроллинг)
 if (ScrollLToR!=0)
 {
  if (ScrollLToR==1)
  {
   Dx+=SpeedLToR;
   Dx%=128;
  }
  if (ScrollLToR==-1)
  {
   Dx-=SpeedLToR;
   Dx%=128;
  }
 }
 if (ScrollUToD!=0)
 {
  if (ScrollUToD==1)
  {
   Dy+=SpeedUToD;
   Dy%=128;
  }
  if (ScrollUToD==-1)
  {
   Dy-=SpeedUToD;
   Dy%=128;
  }
 }
}
