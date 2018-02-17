#ifndef CSEGMENT_H
#define CSEGMENT_H
 
#include "common.h"
#include "formats.h"
#include "crendertexture.h"
#include "crendertexturefollow.h"
#include "crenderlighting.h"
#include "crenderside.h"
#include "csector.h"
 
#include <vector>
using namespace std;
 
#define SIMPLY_SEGMENT 0
#define UPPER_SEGMENT  1
#define LOWER_SEGMENT  2

class CSegment
{
 protected:
  long X1;//���������� ��������
  long Y1;
  long X2;
  long Y2;
  long UpTexture;//������� ��������
  long DownTexture;//������ ��������
  bool Blend;//������������
  bool Frontier;//�������� �� ������� ������ �������
  
  vector<CRenderSide> vector_CRenderSide;//�����������
  long Index;//����� ��������
  long SectorOne;//����� ������ ���� ������� ������� � �������� ����������� �������
  long SectorOneType;//��� �����
  long SectorTwo;//����� ������ ���� ������� ������� � �������� ����������� �������
  long SectorTwoType;//��� �����
  bool Use;//true-������� ��� ���������
  bool PortalDisable;//true-������ ������������ (��� ����� ����� ������� �� ������ �� �����)
  bool ViewBlend;//true-��� �������������� �������, ��� ����� �������

  CSector *cSector_OnePtr;//��������� �� ������ ������
  CSector *cSector_TwoPtr;//��������� �� ������ ������
 public:
  //----------------------------------------------------------------------------
  CSegment();//�����������
  ~CSegment();//����������
  //----------------------------------------------------------------------------
  void Load(FILE *File,CRenderTexture &cRenderTexture,long index);//��������� ��������
  void Delete(void);//������� ��������
  void DrawSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//���������� �������
  void DrawBlendSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//���������� ���������� �������
  void InitState(void);//�������� ������� � �������� ���������
  void Animate(long Tic);
  void AnimateScroll(void);
  void GetCoord(long &x1,long &y1,long &x2,long &y2);//�������� ���������� ��������
  bool GetFrontier(void);//�������� �������� �� ������� ������ �������
  long GetSectorOne(void);//�������� ����� ������� ������� ��������
  long GetSectorTwo(void);//�������� ����� ������� ������� ��������
  long GetSectorOneType(void);//�������� ��� ������� ������� ��������
  long GetSectorTwoType(void);//�������� ��� ������� ������� ��������
  void SetCSectorOnePtr(CSector *cSectorPtr);//���������� ��������� �� ������ ������
  void SetCSectorTwoPtr(CSector *cSectorPtr);//���������� ��������� �� ������ ������
  CSector* GetCSectorOnePtr(void);//�������� ��������� �� ������ ������
  CSector* GetCSectorTwoPtr(void);//�������� ��������� �� ������ ������
  bool GetUse(void);//��������, ��������� �� �������
  void SetPortalDisableState(bool state);//���������� ��������� ���������� �������
  bool GetPortalDisableState(void);//�������� ��������� ���������� �������
  //----------------------------------------------------------------------------
};
#endif
