#ifndef CSIMPLY_DOOR_H
#define CSIMPLY_DOOR_H
 
#include "common.h"
#include "formats.h"
#include "mathematic.h"
#include "crendertexture.h"
#include "crendertexturefollow.h"
#include "crenderlighting.h"
#include "crenderside.h"
#include "csector.h"
 
#include <vector>
using namespace std;
 
class CSimplyDoor:public CSector
{
 protected:
  //������������� ��� ���� ������� ������
  float Dz;//�������� ������ ���� (0-���=�������)
  float Direction;//����������� ��������� ������ (0-��� ���������,1-�����,-1-����)
  long Timer;//����� ���������� ����� � �������� ���������

  long UpLevelCopy; 
  long DownLevelCopy;  
 public:
  //----------------------------------------------------------------------------
  CSimplyDoor(void);
  //----------------------------------------------------------------------------
  void Load(FILE *File,CRenderTexture &cRenderTexture,long index);
  void DrawSector(float PlayerZ,CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);
  void Animate(long Tick);  
  //----------------------------------------------------------------------------
  void Message_HeadImpactCeiling(void);
  void Message_Activate(void);
};
#endif
