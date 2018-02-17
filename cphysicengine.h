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
 float X;//координаты верхнего центра персонажа (персонаж представлен цилиндром)
 float Y;
 float Z;
  
 float Radius;//радиус персонажа
 float Height;//высота персонажа
 float AngleXY;//угол поворота персонажа в плоскости XOY
 float AngleZX;//угол поворота персонажа в плоскости ZOX
  
 long Rise;//1-персонаж поднимается
 float MaxZ;//уровень, до которого нужно поднимать персонаж
};
//------------------------------------------------------------------------------
class CPhysicEngine
{ 
 protected:  
  vector<CSector*> vector_CSectorPtr;//массив указателей на все сектора
  vector<SCharacter> vector_SCharacter;//список существующих персонажей
  vector<long> vector_CollizionSegment;//массив для линий, с которыми столкнулся объект
  vector<CSegment*> vector_CSegmentPtr;//массив указателей на все сегменты
 public:
  CPhysicEngine(void);
  ~CPhysicEngine(void);
  //----------------------------------------------------------------------------
  void SetCharacterInMap(long ch);//создать персонажей
  void DeleteAllCharacterInMap(void);//удалить всех персонажей
  void SetCharacterParameters(long ch,SCharacter sCharacter);//установить параметры персонажа
  void SetCharacterCoord(long ch,float x,float y,float z,float anglexy);//установить координаты персонажа
  void GetCharacterParameters(long ch,SCharacter *sCharacter);//получить параметры персонажа
  long OnCollision(long sgm,float x,float y,float z,float radius,float height,long *rise,float *maxz);//проверка столкновения с сегментом sgm
  void ChangeZCoord(long ch);//вертикальное перемещение персонажа
  long MoveCharacterXY(long ch,float dx,float dy,long step);//переместить персонажа
  void RotateCharacter(long ch,float anglexy,float anglezx);//повернуть персонаж
  void SetCharacterCoordZAtDown(long ch);//поставить персонажа на пол
  void Activate(long ch);//персонаж активирует то что перед ним
  void Processing(void);//цикл обработки персонажей
  //----------------------------------------------------------------------------
  void ClearAllSectorPtr(void);//удалить все указатели на сектора
  void AddSectorPtr(CSector *cSectorPtr);//добавить указатель на сектор
  void ClearAllSegmentPtr(void);//удалить все указатели на сегменты
  void AddSegmentPtr(CSegment *cSegmentPtr);//добавить указатель на сегмент
  CSector* GetCSectorPtrForPoint(float x,float y);//получить указатель на сектор по координатам точки
  CSector* GetCSectorPtrForIndexAndType(long index,long type);//получить указатель на сектор по его номеру и типу
  CSector* GetCSectorPtrForIndex(long index);//получить указатель на сектор по его номеру
  void TransferSectorMessage(CSector *cSectorPtr,long message);//послать сектору сообщение 
}; 
#endif;
