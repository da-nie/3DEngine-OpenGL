#include "csector.h"
#include "cphysicengine.h" 

extern CPhysicEngine cPhysicEngine; 

extern long List;

//------------------------------------------------------------------------------
CSector::CSector(void)
{
}
CSector::~CSector(void)
{
 Delete();
}
//------------------------------------------------------------------------------
void CSector::Load(FILE *File,CRenderTexture &cRenderTexture,long index)
{
 if (File==NULL) return;
 long m; 
 //читаем сектор
 UpLevel=LoadLong(File);
 DownLevel=LoadLong(File);
 UpTexture=LoadLong(File);
 UpTexture=cRenderTexture.AddEnabledTextureIndex(UpTexture);
 DownTexture=LoadLong(File);
 DownTexture=cRenderTexture.AddEnabledTextureIndex(DownTexture);
 Vertex=LoadLong(File);
 for(m=0;m<Vertex;m++)
 {
  X[m]=(long)(LoadFloat(File));
  Y[m]=(long)(LoadFloat(File));
 }
 //загружаем анимацию текстур
 CRenderTextureFollow cRenderTextureFollow_Up;
 CRenderTextureFollow cRenderTextureFollow_Down;
 cRenderTextureFollow_Up.Load(File,cRenderTexture);
 cRenderTextureFollow_Down.Load(File,cRenderTexture);
 //читаем его поверхности
 for(m=0;m<2;m++)
 {
  long location=LoadLong(File);
  CRenderSide cRenderSide;
  cRenderSide.SetBlend(false);
  cRenderSide.SetLocation(location);
  if (location==1) cRenderSide.SetTextureFollow(cRenderTextureFollow_Up);
              else cRenderSide.SetTextureFollow(cRenderTextureFollow_Down);
  cRenderSide.Load(File);
  //генерируем список
  cRenderSide.CreateList(List);
  vector_CRenderSide.push_back(cRenderSide);
 }
 SectorType=SECTOR_TYPE_SIMPLY_SECTOR;
 UpDz=0;
 DownDz=0;
 Index=index;
}
void CSector::Delete(void)
{

}
void CSector::DrawSector(float PlayerZ,CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting)
{
 if (Use==false)//этот сектор ещё не выводился
 {
  Use=true;
  //выведем полы и потолки
  long side=vector_CRenderSide.size();
  for(long m=0;m<side;m++)
  {
   if (m==0 && UpLevel<=PlayerZ) continue;
   if (m==1 && DownLevel>=PlayerZ) continue;
   vector_CRenderSide[m].Translate(0,0,0);
   vector_CRenderSide[m].Draw(cRenderTexture,cRenderLighting);
  }
 }
}
void CSector::SetState(void)
{
 Use=false;
}
bool CSector::CheckPointInSector(float x,float y)
{ 
 long pos=0;
 for(long m=0;m<Vertex;m++)
 {
  long i1=m;
  long i2=m+1;
  if (i2>=Vertex) i2-=Vertex;
  float xw1=(float)(X[i1]);
  float yw1=(float)(Y[i1]);
  float xw2=(float)(X[i2]);
  float yw2=(float)(Y[i2]);
  float res=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
  if (res<=-EPS) res=-1;
  if (res>=EPS) res=1;
  if (res>-EPS && res<EPS) res=0;
  if (res==0) continue;
  if (pos==0) pos=(long)(res);
  if (pos!=(long)(res)) return(false);
 }
 return(true);
}
void CSector::Animate(long Tick)
{
 if (Tick==1) return;
 long side=vector_CRenderSide.size();
 for(long m=0;m<side;m++) vector_CRenderSide[m].Processing();
}
void CSector::AnimateScroll(void)
{
}
//получить уровень потолка
long CSector::GetUpLevel(void)
{
 return(UpLevel);
}
//получить уровень пола
long CSector::GetDownLevel(void)
{
 return(DownLevel);
}
//получить тип сектора
long CSector::GetSectorType(void)
{
 return(SectorType);
}
//получить смещение верхних линий
long CSector::GetUpDz(void)
{
 return(UpDz);
}
//получить смещение нижних линий
long CSector::GetDownDz(void)
{
 return(DownDz);
}

//очистить список порталов
void CSector::ClearPortalList(void)
{
 vector_PortalList.clear();
}
//очистить список доступных порталов
void CSector::ClearEnabledPortalList(void)
{
 vector_EnabledPortalList.clear();
}
//очистить список сегментов
void CSector::ClearSegmentList(void)
{
 vector_SegmentList.clear();
}
//добавить индекс портала
void CSector::AddPortalIndex(long portal_index)
{
 vector_PortalList.push_back(portal_index);
}
//добавить индекс доступного портала
void CSector::AddEnabledPortalIndex(long portal_index)
{
 vector_EnabledPortalList.push_back(portal_index);
}
//добавить индекс сегмента
void CSector::AddSegmentIndex(long segment_index)
{
 vector_SegmentList.push_back(segment_index);
}
//получить индекс портала
long CSector::GetPortalIndex(long index)
{
 if (index>=vector_PortalList.size()) return(-1);
 return(vector_PortalList[index]);
}
//получить индекс доступного портала
long CSector::GetEnabledPortalIndex(long index)
{
 if (index>=vector_EnabledPortalList.size()) return(-1);
 return(vector_EnabledPortalList[index]);
}
//получить индекс сегмента
long CSector::GetSegmentIndex(long index)
{
 if (index>=vector_SegmentList.size()) return(-1);
 return(vector_SegmentList[index]);
}
//получить индекс сектора
long CSector::GetSectorIndex(void)
{
 return(Index);
}
