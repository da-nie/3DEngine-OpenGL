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
  long X1;//координаты сегмента
  long Y1;
  long X2;
  long Y2;
  long UpTexture;//верхняя текстура
  long DownTexture;//нижняя текстура
  bool Blend;//прозрачность
  bool Frontier;//является ли сегмент линией раздела
  
  vector<CRenderSide> vector_CRenderSide;//поверхности
  long Index;//номер сегмента
  long SectorOne;//номер внутри типа первого сектора к которому принадлежит сегмент
  long SectorOneType;//его класс
  long SectorTwo;//номер внутри типа второго сектора к которому принадлежит сегмент
  long SectorTwoType;//его класс
  bool Use;//true-сегмент уже выводился
  bool PortalDisable;//true-портал заблокирован (это нужно чтобы сектора не ходили по кругу)
  bool ViewBlend;//true-это полупрозрачный сегмент, его нужно вывести

  CSector *cSector_OnePtr;//указатель на первый сектор
  CSector *cSector_TwoPtr;//указатель на второй сектор
 public:
  //----------------------------------------------------------------------------
  CSegment();//конструктор
  ~CSegment();//деструктор
  //----------------------------------------------------------------------------
  void Load(FILE *File,CRenderTexture &cRenderTexture,long index);//загрузить сегменты
  void Delete(void);//удалить сегменты
  void DrawSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//отрисовать сегмент
  void DrawBlendSegment(CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting);//отрисовать прозрачный сегмент
  void InitState(void);//привести сегмент в исходное состояние
  void Animate(long Tic);
  void AnimateScroll(void);
  void GetCoord(long &x1,long &y1,long &x2,long &y2);//получить координаты сегмента
  bool GetFrontier(void);//получить является ли сегмент линией раздела
  long GetSectorOne(void);//получить номер первого сектора сегмента
  long GetSectorTwo(void);//получить номер второго сектора сегмента
  long GetSectorOneType(void);//получить тип первого сектора сегмента
  long GetSectorTwoType(void);//получить тип второго сектора сегмента
  void SetCSectorOnePtr(CSector *cSectorPtr);//установить указатель на первый сектор
  void SetCSectorTwoPtr(CSector *cSectorPtr);//установить указатель на второй сектор
  CSector* GetCSectorOnePtr(void);//получить указатель на первый сектор
  CSector* GetCSectorTwoPtr(void);//получить указатель на второй сектор
  bool GetUse(void);//получить, выводился ли сегмент
  void SetPortalDisableState(bool state);//установить состояние блокировки портала
  bool GetPortalDisableState(void);//получить состояние блокировки портала
  //----------------------------------------------------------------------------
};
#endif
