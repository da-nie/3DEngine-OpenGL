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

//обычный сектор
#define SECTOR_TYPE_SIMPLY_SECTOR 0
//обычная дверь
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
  long SectorType;//тип сектора
  long UpDz;//смещения по высоте для верхних линий
  long DownDz;//смещения по высоте для нижних линий
  long Index;//индекс сектора внутри своего типа

  vector<CRenderSide> vector_CRenderSide;//поверхности  
  vector<long> vector_SegmentList;//список сегментов сектора
  vector<long> vector_PortalList;//список порталов сектора
  vector<long> vector_EnabledPortalList;//список доступных порталов сектора(заполняется в процесе работы)

  bool Use;//сектор уже выводился
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
  long GetUpLevel(void);//получить уровень потолка
  long GetDownLevel(void);//получить уровень пола
  long GetSectorType(void);//получить тип сектора
  long GetUpDz(void);//получить смещение верхних линий
  long GetDownDz(void);//получить смещение нижних линий
  void ClearPortalList(void);//очистить список порталов
  void ClearEnabledPortalList(void);//очистить список доступных порталов
  void ClearSegmentList(void);//очистить список сегментов
  void AddPortalIndex(long portal_index);//добавить индекс портала
  void AddEnabledPortalIndex(long portal_index);//добавить индекс доступного портала
  void AddSegmentIndex(long segment_index);//добавить индекс сегмента
  long GetPortalIndex(long index);//получить индекс портала
  long GetEnabledPortalIndex(long index);//получить индекс доступного портала
  long GetSegmentIndex(long index);//получить индекс сегмента
  long GetSectorIndex(void);//получить индекс сектора
  //----------------------------------------------------------------------------
};
#endif
