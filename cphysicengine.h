#ifndef CBASIS_ENGINE_H
#define CBASIS_ENGINE_H
 
#define PHE_HEAD_IMPACT_CEILING 100
#define PHE_ACTIVATE            101
 
#include <vector>
#include <math.h>
#include "mathematic.h"
#include "csimplydoor.h"
#include "csimplysector.h"
#include "csector.h"
#include "csegment.h"

using namespace std;
 
struct SCharacter
{
 float X;//���������� �������� ������ ��������� (�������� ����������� ���������)
 float Y;
 float Z;
  
 float Radius;//������ ���������
 float Height;//������ ���������
 float AngleXY;//���� �������� ��������� � ��������� XOY
 float AngleZX;//���� �������� ��������� � ��������� ZOX
  
 long Rise;//1-�������� �����������
 float MaxZ;//�������, �� �������� ����� ��������� ��������
};
//------------------------------------------------------------------------------
class CPhysicEngine
{ 
 protected:  
  vector<CSector*> vector_CSectorPtr;//������ ���������� �� ��� �������
  vector<SCharacter> vector_SCharacter;//������ ������������ ����������
  vector<long> vector_CollizionSegment;//������ ��� �����, � �������� ���������� ������
  vector<CSegment*> vector_CSegmentPtr;//������ ���������� �� ��� ��������
 public:
  CPhysicEngine(void);
  ~CPhysicEngine(void);
  //----------------------------------------------------------------------------
  void SetCharacterInMap(long ch);//������� ����������
  void DeleteAllCharacterInMap(void);//������� ���� ����������
  void SetCharacterParameters(long ch,SCharacter sCharacter);//���������� ��������� ���������
  void SetCharacterCoord(long ch,float x,float y,float z,float anglexy);//���������� ���������� ���������
  void GetCharacterParameters(long ch,SCharacter *sCharacter);//�������� ��������� ���������
  long OnCollision(long sgm,float x,float y,float z,float radius,float height,long *rise,float *maxz);//�������� ������������ � ��������� sgm
  void ChangeZCoord(long ch);//������������ ����������� ���������
  long MoveCharacterXY(long ch,float dx,float dy,long step);//����������� ���������
  void RotateCharacter(long ch,float anglexy,float anglezx);//��������� ��������
  void SetCharacterCoordZAtDown(long ch);//��������� ��������� �� ���
  void Activate(long ch);//�������� ���������� �� ��� ����� ���
  void Processing(void);//���� ��������� ����������
  //----------------------------------------------------------------------------
  void ClearAllSectorPtr(void);//������� ��� ��������� �� �������
  void AddSectorPtr(CSector *cSectorPtr);//�������� ��������� �� ������
  void ClearAllSegmentPtr(void);//������� ��� ��������� �� ��������
  void AddSegmentPtr(CSegment *cSegmentPtr);//�������� ��������� �� �������
  CSector* GetCSectorPtrForPoint(float x,float y);//�������� ��������� �� ������ �� ����������� �����
  CSector* GetCSectorPtrForIndexAndType(long index,long type);//�������� ��������� �� ������ �� ��� ������ � ����
  CSector* GetCSectorPtrForIndex(long index);//�������� ��������� �� ������ �� ��� ������
  void TransferSectorMessage(CSector *cSectorPtr,long message);//������� ������� ��������� 
}; 
#endif;
