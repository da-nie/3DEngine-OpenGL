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
 //������ ������
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
 //��������� �������� �������
 CRenderTextureFollow cRenderTextureFollow_Up;
 CRenderTextureFollow cRenderTextureFollow_Down;
 cRenderTextureFollow_Up.Load(File,cRenderTexture);
 cRenderTextureFollow_Down.Load(File,cRenderTexture);
 //������ ��� �����������
 for(m=0;m<2;m++)
 {
  long location=LoadLong(File);
  CRenderSide cRenderSide;
  cRenderSide.SetBlend(false);
  cRenderSide.SetLocation(location);
  if (location==1) cRenderSide.SetTextureFollow(cRenderTextureFollow_Up);
              else cRenderSide.SetTextureFollow(cRenderTextureFollow_Down);
  cRenderSide.Load(File);
  //���������� ������
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
 if (Use==false)//���� ������ ��� �� ���������
 {
  Use=true;
  //������� ���� � �������
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
//�������� ������� �������
long CSector::GetUpLevel(void)
{
 return(UpLevel);
}
//�������� ������� ����
long CSector::GetDownLevel(void)
{
 return(DownLevel);
}
//�������� ��� �������
long CSector::GetSectorType(void)
{
 return(SectorType);
}
//�������� �������� ������� �����
long CSector::GetUpDz(void)
{
 return(UpDz);
}
//�������� �������� ������ �����
long CSector::GetDownDz(void)
{
 return(DownDz);
}

//�������� ������ ��������
void CSector::ClearPortalList(void)
{
 vector_PortalList.clear();
}
//�������� ������ ��������� ��������
void CSector::ClearEnabledPortalList(void)
{
 vector_EnabledPortalList.clear();
}
//�������� ������ ���������
void CSector::ClearSegmentList(void)
{
 vector_SegmentList.clear();
}
//�������� ������ �������
void CSector::AddPortalIndex(long portal_index)
{
 vector_PortalList.push_back(portal_index);
}
//�������� ������ ���������� �������
void CSector::AddEnabledPortalIndex(long portal_index)
{
 vector_EnabledPortalList.push_back(portal_index);
}
//�������� ������ ��������
void CSector::AddSegmentIndex(long segment_index)
{
 vector_SegmentList.push_back(segment_index);
}
//�������� ������ �������
long CSector::GetPortalIndex(long index)
{
 if (index>=vector_PortalList.size()) return(-1);
 return(vector_PortalList[index]);
}
//�������� ������ ���������� �������
long CSector::GetEnabledPortalIndex(long index)
{
 if (index>=vector_EnabledPortalList.size()) return(-1);
 return(vector_EnabledPortalList[index]);
}
//�������� ������ ��������
long CSector::GetSegmentIndex(long index)
{
 if (index>=vector_SegmentList.size()) return(-1);
 return(vector_SegmentList[index]);
}
//�������� ������ �������
long CSector::GetSectorIndex(void)
{
 return(Index);
}
