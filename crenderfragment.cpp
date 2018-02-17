#include "crenderfragment.h"

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CRenderFragment::CRenderFragment(void)
{
 vector_SVertex.clear();
 List=0;
 NormalArray=NULL;
 VertexArray=NULL;
 TextureArray=NULL;
 FaceArray=NULL;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRenderFragment::~CRenderFragment(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//конструктор копий
//----------------------------------------------------------------------------------------------------
CRenderFragment::CRenderFragment(const CRenderFragment& cRenderFragment)
{
 long n; 
 List=cRenderFragment.List;
 Vertex=cRenderFragment.Vertex;
 N_X=cRenderFragment.N_X;
 N_Y=cRenderFragment.N_Y;
 N_Z=cRenderFragment.N_Z;
 for(n=0;n<8;n++) LightingState[n]=cRenderFragment.LightingState[n];
 vector_SVertex=cRenderFragment.vector_SVertex;
 long size=vector_SVertex.size();

 NormalArray=NULL;
 VertexArray=NULL;
 TextureArray=NULL;
 FaceArray=NULL;

 if (cRenderFragment.NormalArray!=NULL)
 {
  NormalArray=new float[size*3];
  for(n=0;n<size*3;n++) NormalArray[n]=cRenderFragment.NormalArray[n];
 }
 if (cRenderFragment.VertexArray!=NULL)
 {
  VertexArray=new float[size*3];
  for(n=0;n<size*3;n++) VertexArray[n]=cRenderFragment.VertexArray[n];
 }
 if (cRenderFragment.TextureArray!=NULL)
 {
  TextureArray=new float[size*2];
  for(n=0;n<size*2;n++) TextureArray[n]=cRenderFragment.TextureArray[n];
 }
 if (cRenderFragment.FaceArray!=NULL)
 {
  FaceArray=new GLint[size];
  for(n=0;n<size;n++) FaceArray[n]=cRenderFragment.FaceArray[n];
 }
}
//----------------------------------------------------------------------------------------------------
//операция присваивания
//----------------------------------------------------------------------------------------------------
CRenderFragment& CRenderFragment::operator=(const CRenderFragment& cRenderFragment)
{
 if (this==&cRenderFragment) return (*this);//проверка на присваивание себе

 if (NormalArray!=NULL) delete[](NormalArray);
 if (VertexArray!=NULL) delete[](VertexArray);
 if (TextureArray!=NULL) delete[](TextureArray);
 if (FaceArray!=NULL) delete[](FaceArray);

 NormalArray=NULL;
 VertexArray=NULL;
 TextureArray=NULL;
 FaceArray=NULL;


 long n; 
 List=cRenderFragment.List;
 Vertex=cRenderFragment.Vertex;
 N_X=cRenderFragment.N_X;
 N_Y=cRenderFragment.N_Y;
 N_Z=cRenderFragment.N_Z;
 for(n=0;n<8;n++) LightingState[n]=cRenderFragment.LightingState[n];
 vector_SVertex=cRenderFragment.vector_SVertex;
 long size=vector_SVertex.size();
  
 if (cRenderFragment.NormalArray!=NULL)
 {
  NormalArray=new float[size*3];
  for(n=0;n<size*3;n++) NormalArray[n]=cRenderFragment.NormalArray[n];
 }
 if (cRenderFragment.VertexArray!=NULL)
 {
  VertexArray=new float[size*3];
  for(n=0;n<size*3;n++) VertexArray[n]=cRenderFragment.VertexArray[n];
 }
 if (cRenderFragment.TextureArray!=NULL)
 {
  TextureArray=new float[size*2];
  for(n=0;n<size*2;n++) TextureArray[n]=cRenderFragment.TextureArray[n];
 }
 if (cRenderFragment.FaceArray!=NULL)
 {
  FaceArray=new GLint[size];
  for(n=0;n<size;n++) FaceArray[n]=cRenderFragment.FaceArray[n];
 }
 return (*this);//возврат ссылки на объект
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
 glNormalPointer(GL_FLOAT,0,NormalArray);
 glVertexPointer(3,GL_FLOAT,0,VertexArray);
 glTexCoordPointer(2,GL_FLOAT,0,TextureArray);

 glDrawElements(GL_TRIANGLE_FAN,Vertex,GL_UNSIGNED_INT,FaceArray);
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
 if (NormalArray!=NULL) delete[](NormalArray);
 if (VertexArray!=NULL) delete[](VertexArray);
 if (TextureArray!=NULL) delete[](TextureArray);
 if (FaceArray!=NULL) delete[](FaceArray);
 NormalArray=NULL;
 VertexArray=NULL;
 TextureArray=NULL;
 FaceArray=NULL;
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
 if (NormalArray!=NULL) delete[](NormalArray);
 if (VertexArray!=NULL) delete[](VertexArray);
 if (TextureArray!=NULL) delete[](TextureArray);
 if (FaceArray!=NULL) delete[](FaceArray);

 long size=vector_SVertex.size();

 NormalArray=new float[size*3];
 VertexArray=new float[size*3];
 TextureArray=new float[size*2];
 FaceArray=new GLint[size]; 

 for(long n=0;n<size;n++)
 {
  long index=n*3;
  NormalArray[index+0]=N_X;
  NormalArray[index+1]=N_Y;
  NormalArray[index+2]=N_Z;

  VertexArray[index+0]=vector_SVertex[n].X;
  VertexArray[index+1]=vector_SVertex[n].Y;
  VertexArray[index+2]=vector_SVertex[n].Z;

  index=n*2;
  TextureArray[index+0]=vector_SVertex[n].TV;
  TextureArray[index+1]=vector_SVertex[n].TU;

  FaceArray[n]=n;
 }
}
