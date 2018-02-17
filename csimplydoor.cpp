#include "csimplydoor.h"
#include "cphysicengine.h" 
 
extern CPhysicEngine cPhysicEngine; 

extern long List;
 
//------------------------------------------------------------------------------
CSimplyDoor::CSimplyDoor(void)
{
}
//------------------------------------------------------------------------------
void CSimplyDoor::Load(FILE *File,CRenderTexture &cRenderTexture,long index)
{
 CSector::Load(File,cRenderTexture,index);
 SectorType=SECTOR_TYPE_SIMPLY_DOOR;
 Direction=0;
 Dz=0;
 Timer=0;
 UpLevelCopy=UpLevel;
 DownLevelCopy=DownLevel;
}

void CSimplyDoor::DrawSector(float PlayerZ,CRenderTexture &cRenderTexture,CRenderLighting &cRenderLighting)
{
 if (Use==false)//этот сектор ещё не выводился
 {
  Use=true;
  //выведем полы и потолки
  long side=vector_CRenderSide.size();
  for(long m=0;m<side;m++)
  {
   if (m==0 && UpLevelCopy<=PlayerZ) continue;
   if (m==1 && UpLevelCopy-Dz>=PlayerZ) continue;
   vector_CRenderSide[m].Translate(0,0,0);
   if (vector_CRenderSide[m].GetLocation()==2) vector_CRenderSide[m].Translate(0,-Dz,0);
   vector_CRenderSide[m].Draw(cRenderTexture,cRenderLighting);
  }
 } 
}
void CSimplyDoor::Animate(long Tick)
{
 //обработка изменений высоты
 if (Timer==0) Dz+=Direction;
 if (Timer>0) Timer--;
 if (Dz>UpLevelCopy-DownLevelCopy)
 {
  Dz=(float)UpLevelCopy-DownLevelCopy;
  Timer=200;
  Direction=-Direction;
 }
 if (Dz<0)
 {
  Dz=0;
  Direction=0;
  Timer=0;
 }
 DownLevel=UpLevelCopy-Dz;
 DownDz=(long)-Dz;
 UpDz=-0; 
 //анимация текстуры
 if (Tick==1) return;
 long side=vector_CRenderSide.size();
 for(long m=0;m<side;m++) vector_CRenderSide[m].Processing();
}
//------------------------------------------------------------------------------
void CSimplyDoor::Message_HeadImpactCeiling(void)
{
 Direction=3; 
}
void CSimplyDoor::Message_Activate(void)
{
 Direction=3;
}
