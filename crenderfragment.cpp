#include "crenderfragment.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CRenderFragment::CRenderFragment(void)
{
 vector_SVertex.clear();
 List=0;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRenderFragment::~CRenderFragment(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderFragment::Draw(void)
{
 //включим или выключим нужные источники OpenGL
 if (LightingState[0]==true) glEnable(GL_LIGHT0);
                        else glDisable(GL_LIGHT0);
 if (LightingState[1]==true) glEnable(GL_LIGHT1);
                        else glDisable(GL_LIGHT1);
 if (LightingState[2]==true) glEnable(GL_LIGHT2);
                        else glDisable(GL_LIGHT2);
 if (LightingState[3]==true) glEnable(GL_LIGHT3);
                        else glDisable(GL_LIGHT3);
 if (LightingState[4]==true) glEnable(GL_LIGHT4);
                        else glDisable(GL_LIGHT4);
 if (LightingState[5]==true) glEnable(GL_LIGHT5);
                        else glDisable(GL_LIGHT5);
 if (LightingState[6]==true) glEnable(GL_LIGHT6);
                        else glDisable(GL_LIGHT6);
 if (LightingState[7]==true) glEnable(GL_LIGHT7);
                        else glDisable(GL_LIGHT7);
 //выводим фрагмент
 glCallList(List);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderFragment::Load(FILE *File)
{
 long n;
 vector_SVertex.clear();
 //читаем состояния источников света
 unsigned char lightinstate=LoadChar(File);
 long mask=1;
 for(n=0;n<8;n++,mask<<=1)
 {
  if (lightinstate&mask) LightingState[n]=true;
                    else LightingState[n]=false;
 }
 //читаем число вершин полигона
 Vertex=LoadLong(File);
 for(n=0;n<Vertex;n++)
 {
  SVertex sVertex;
  sVertex.X=LoadFloat(File);
  sVertex.Y=LoadFloat(File);
  sVertex.Z=LoadFloat(File);
  sVertex.TU=LoadFloat(File);
  sVertex.TV=LoadFloat(File);
  vector_SVertex.push_back(sVertex);
 }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderFragment::Release(void)
{
 vector_SVertex.clear();
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderFragment::SetNormal(float nx,float ny,float nz)
{
 N_X=nx;
 N_Y=ny;
 N_Z=nz;
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void CRenderFragment::CreateList(long &list)
{
 List=list;
 long size=vector_SVertex.size();
 glNewList(list,GL_COMPILE);
 glNormal3f(N_X,N_Y,N_Z);
 glBegin(GL_POLYGON);
 for(long n=0;n<size;n++)
 {
  glTexCoord2f(vector_SVertex[n].TV,vector_SVertex[n].TU);
  glVertex3f(vector_SVertex[n].X,vector_SVertex[n].Y,vector_SVertex[n].Z);
 }
 glEnd();
 glEndList();
 list++;
}
