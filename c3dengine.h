#ifndef CENGINE_H
#define CENGINE_H
 
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
 
#include "common.h"

#include "cphysicengine.h"
#include "csimplydoor.h"
#include "csimplysector.h"
#include "csegment.h"
#include "crendertexture.h"
#include "crenderlighting.h"
 
class C3DEngine
{
 protected:
  vector<CSimplySector> vector_CSimplySector;//������� �������
  vector<CSimplyDoor> vector_CSimplyDoor;//������� �����
  vector<CSegment> vector_CSegment;//��������
  SFogSetting sFogSetting;
  CRenderTexture cRenderTexture;//����� �������� �������
  CRenderLighting cRenderLighting;//��������� �����
 public:
  C3DEngine(void);//�����������
 public:
  void LoadSegment(char *FileName);
  void LoadSimplySector(char *FileName);
  void LoadSimplyDoor(char *FileName);
  void LoadTexture(char *FileName);
  void LoadStage(char *FileName);
  void LoadFogParameters(char *FileName);
  void LoadLighting(char *FileName);
  void SetSurround(void);
  void DefinitionSegmentAndPortal(void);
  void DrawBlendSegment(void);
  void DrawStage(SPortalComponent sPortalComponent,SCharacter *sCharacter);
  void Draw(SCharacter *sCharacter);
  void Animate(long Tick);
  void AnimateScroll(void);
  void AnimateLighting(void);  
  void DeleteStage(void);
};
#endif
