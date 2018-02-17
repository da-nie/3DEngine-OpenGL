#ifndef CSECTOR_H
#define CSECTOR_H
 
#include "formats.h"
#include "mathematic.h"
#include "crendertexture.h"
#include "crendertexturefollow.h"
#include "crenderlighting.h"
#include "crenderside.h"

#include <vector>
using namespace std;

//������� ������
#define SECTOR_TYPE_SIMPLY_SECTOR 0
//������� �����
#define SECTOR_TYPE_SIMPLY_DOOR   1

class CSector
{
 protected:
  long Vertex;
  long X[100];
  long Y[100];
  long UpLevel;
  long DownLevel;
  long UpTexture;
  long DownTexture;
  long SectorType;//��� �������
  long UpDz;//�������� �� ������ ��� ������� �����
  long DownDz;//�������� �� ������ ��� ������ �����
  long Index;//������ ������� ������ ������ ����

  vector<CRenderSide> vector_CRenderSide;//�����������  
  vector<long> vector_SegmentList;//������ ��������� �������
  vector<long> vector_PortalList;//������ �������� �������
  vector<long> vector_EnabledPortalList;//������ ��������� �������� �������(����������� � ������� ������)

  bool Use;//������ ��� ���������
 public:  
  //----------------------------------------------------------------------------
  CSector(void);
  ~CSector(void);
  //----------------------------------------------------------------------------
  void Load(FILE *File,CRenderTexture &cRenderTexture,long index);
  void Delete(void);
  void DrawSector(float PlayerZ,CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);
  void SetState(void);
  bool CheckPointInSector(float x,float y);
  void Animate(long Tick);
  void AnimateScroll(void);
  long GetUpLevel(void);//�������� ������� �������
  long GetDownLevel(void);//�������� ������� ����
  long GetSectorType(void);//�������� ��� �������
  long GetUpDz(void);//�������� �������� ������� �����
  long GetDownDz(void);//�������� �������� ������ �����
  void ClearPortalList(void);//�������� ������ ��������
  void ClearEnabledPortalList(void);//�������� ������ ��������� ��������
  void ClearSegmentList(void);//�������� ������ ���������
  void AddPortalIndex(long portal_index);//�������� ������ �������
  void AddEnabledPortalIndex(long portal_index);//�������� ������ ���������� �������
  void AddSegmentIndex(long segment_index);//�������� ������ ��������
  long GetPortalIndex(long index);//�������� ������ �������
  long GetEnabledPortalIndex(long index);//�������� ������ ���������� �������
  long GetSegmentIndex(long index);//�������� ������ ��������
  long GetSectorIndex(void);//�������� ������ �������
  //----------------------------------------------------------------------------
};
#endif
