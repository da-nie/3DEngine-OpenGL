#include "csegment.h"
#include "cphysicengine.h"
 
extern CPhysicEngine cPhysicEngine;
 
extern long List;
 
//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CSegment::CSegment()
{ 
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CSegment::~CSegment()
{
 Delete();
}
 
//----------------------------------------------------------------------------------------------------
//загрузить сегмент
//----------------------------------------------------------------------------------------------------
void CSegment::Load(FILE *File,CRenderTexture &cRenderTexture,long index)
{ 
 X1=(long)(LoadFloat(File));
 Y1=(long)(LoadFloat(File));
 X2=(long)(LoadFloat(File));
 Y2=(long)(LoadFloat(File));
 UpTexture=LoadLong(File);
 UpTexture=cRenderTexture.AddEnabledTextureIndex(UpTexture);
 DownTexture=LoadLong(File);
 DownTexture=cRenderTexture.AddEnabledTextureIndex(DownTexture);
 Blend=false;
 if (LoadChar(File)!=0) Blend=true;
 Frontier=false;
 if (LoadChar(File)!=0) Frontier=true;
 SectorOne=LoadLong(File);
 SectorOneType=LoadShort(File);
 SectorTwo=LoadLong(File);
 SectorTwoType=LoadShort(File);
 //загружаем анимацию текстуры
 CRenderTextureFollow cRenderTextureFollow_Up;
 CRenderTextureFollow cRenderTextureFollow_Down;
 cRenderTextureFollow_Up.Load(File,cRenderTexture);
 cRenderTextureFollow_Down.Load(File,cRenderTexture);
 vector_CRenderSide.clear();
 //читаем поверхности сегмента
 long side=LoadLong(File);
 for(long m=0;m<side;m++)
 {
  //положение
  long location=LoadLong(File);
  CRenderSide cRenderSide;
  cRenderSide.SetBlend(Blend);
  cRenderSide.SetLocation(location);
  if (location==SIMPLY_SEGMENT || location==UPPER_SEGMENT) cRenderSide.SetTextureFollow(cRenderTextureFollow_Up);
                                                      else cRenderSide.SetTextureFollow(cRenderTextureFollow_Down);
  cRenderSide.Load(File);
  //генерируем список
  cRenderSide.CreateList(List);
  vector_CRenderSide.push_back(cRenderSide);
 }
 Index=index;
}
//----------------------------------------------------------------------------------------------------
//удалить сегменты
//----------------------------------------------------------------------------------------------------
void CSegment::Delete(void)
{
 vector_CRenderSide.clear();
}
//----------------------------------------------------------------------------------------------------
//отрисовать сегмент
//----------------------------------------------------------------------------------------------------
void CSegment::DrawSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting)
{ 
 if (Use==true) return;//сегмент уже выводился
 long side=vector_CRenderSide.size();
 for(long m=0;m<side;m++)
 {
  if (Blend==true)
  {
   ViewBlend=true;
   continue;
  }
  vector_CRenderSide[m].Translate(0,0,0);
  if (Frontier==true)   
  {
   //выводим все фрагменты
   if (vector_CRenderSide[m].GetLocation()==LOWER_SEGMENT) vector_CRenderSide[m].Translate(0,cSector_OnePtr->GetDownDz()+cSector_TwoPtr->GetDownDz(),0);
   if (vector_CRenderSide[m].GetLocation()==UPPER_SEGMENT) vector_CRenderSide[m].Translate(0,cSector_OnePtr->GetUpDz()+cSector_TwoPtr->GetUpDz(),0);
   vector_CRenderSide[m].Draw(cRenderTexture,cRenderLighting);
  }
  else vector_CRenderSide[m].Draw(cRenderTexture,cRenderLighting);
 }
 Use=true;
}
//----------------------------------------------------------------------------------------------------
//отрисовать прозрачный сегмент
//----------------------------------------------------------------------------------------------------
void CSegment::DrawBlendSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting)
{
 if (ViewBlend==false) return;
 long side=vector_CRenderSide.size();
 for(long m=0;m<side;m++)
 {
  vector_CRenderSide[m].Translate(0,0,0);
  vector_CRenderSide[m].Draw(cRenderTexture,cRenderLighting);
 }
}
void CSegment::InitState(void)
{
 Use=false;
 PortalDisable=false;
 ViewBlend=false;
}
void CSegment::Animate(long Tick)
{
 if (Tick==1) return;
 long side=vector_CRenderSide.size();
 for(long m=0;m<side;m++) vector_CRenderSide[m].Processing();
}
void CSegment::AnimateScroll(void)
{
}
//----------------------------------------------------------------------------------------------------
//получить координаты сегмента
//----------------------------------------------------------------------------------------------------
void CSegment::GetCoord(long &x1,long &y1,long &x2,long &y2)
{
 x1=X1;
 y1=Y1;
 x2=X2;
 y2=Y2;
}
//----------------------------------------------------------------------------------------------------
//получить является ли сегмент линией раздела
//----------------------------------------------------------------------------------------------------
bool CSegment::GetFrontier(void)
{
 return(Frontier);
}
//----------------------------------------------------------------------------------------------------
//получить номер первого сектора сегмента
//----------------------------------------------------------------------------------------------------
long CSegment::GetSectorOne(void)
{
 return(SectorOne);
}
//----------------------------------------------------------------------------------------------------
//получить номер второго сектора сегмента
//----------------------------------------------------------------------------------------------------
long CSegment::GetSectorTwo(void)
{
 return(SectorTwo);
}
//----------------------------------------------------------------------------------------------------
//получить тип первого сектора сегмента
//----------------------------------------------------------------------------------------------------
long CSegment::GetSectorOneType(void)
{
 return(SectorOneType);
}
//----------------------------------------------------------------------------------------------------
//получить тип второго сектора сегмента
//----------------------------------------------------------------------------------------------------
long CSegment::GetSectorTwoType(void)
{
 return(SectorTwoType);
}
//----------------------------------------------------------------------------------------------------
//установить указатель на первый сектор
//----------------------------------------------------------------------------------------------------
void CSegment::SetCSectorOnePtr(CSector *cSectorPtr)
{
 cSector_OnePtr=cSectorPtr;
}
//----------------------------------------------------------------------------------------------------
//установить указатель на второй сектор
//----------------------------------------------------------------------------------------------------
void CSegment::SetCSectorTwoPtr(CSector *cSectorPtr)
{
 cSector_TwoPtr=cSectorPtr;
}
//----------------------------------------------------------------------------------------------------
//получить указатель на первый сектор
//----------------------------------------------------------------------------------------------------
CSector* CSegment::GetCSectorOnePtr(void)
{
 return(cSector_OnePtr);
}
//----------------------------------------------------------------------------------------------------
//получить указатель на второй сектор
//----------------------------------------------------------------------------------------------------
CSector* CSegment::GetCSectorTwoPtr(void)
{
 return(cSector_TwoPtr);
}
//----------------------------------------------------------------------------------------------------
//получить, выводился ли сегмент 
//----------------------------------------------------------------------------------------------------
bool CSegment::GetUse(void)
{
 return(Use);
}
//----------------------------------------------------------------------------------------------------
//установить состояние блокировки портала
//----------------------------------------------------------------------------------------------------
void CSegment::SetPortalDisableState(bool state)
{
 PortalDisable=state;
}
//----------------------------------------------------------------------------------------------------
//получить состояние блокировки портала
//----------------------------------------------------------------------------------------------------
bool CSegment::GetPortalDisableState(void)
{
 return(PortalDisable);
}
