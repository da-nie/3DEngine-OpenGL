#include "crendertexture.h"

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CRenderTexture::CRenderTexture(void)
{
 vector_TextureEnabledIndex.clear(); 
 TextureList_Array=NULL;
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CRenderTexture::~CRenderTexture(void)
{
 Release();
}
//----------------------------------------------------------------------------------------------------
//���������� �������
//----------------------------------------------------------------------------------------------------
void CRenderTexture::Release(void)
{
 vector_TextureEnabledIndex.clear(); 
 if (TextureList_Array!=NULL) delete(TextureList_Array);
 TextureList_Array=NULL;
}
//----------------------------------------------------------------------------------------------------
//�������� � ������ ������������ ��� ���� �������� (���������� � ����� � ������)
//----------------------------------------------------------------------------------------------------
long CRenderTexture::AddEnabledTextureIndex(long texture_index)
{
 //���� �������� ����� ��� ���������
 long size=vector_TextureEnabledIndex.size();
 for(long n=0;n<size;n++)
 {
  if (vector_TextureEnabledIndex[n]==texture_index) return(n);//����� ��� ����
 }
 //��������� �������� � ������ ������������
 vector_TextureEnabledIndex.push_back(texture_index);
 //���������� � ����� � ������ ������������ (�� ����� ���������� ������� � ������ �� ����������� ����� ��������)
 return(size);
}
//----------------------------------------------------------------------------------------------------
//��������� �������� � ���������� �� � OpenGL
//----------------------------------------------------------------------------------------------------
bool CRenderTexture::LoadAndBuildGLTexture(char *FileName)
{
 long n;
 if (TextureList_Array!=NULL) delete(TextureList_Array);
 TextureList_Array=NULL;
 unsigned char R[256];
 unsigned char G[256];
 unsigned char B[256];
 FILE *file=fopen(FileName,"rb");
 if (file==NULL) return(false);
 long TextureAmount=(long)LoadShort(file);
 long *TextureOffsetList=new long[TextureAmount+1];//������ �������� ������� � �����
 for(n=0;n<TextureAmount;n++) TextureOffsetList[n]=LoadLong(file);
 //��������� ������ �� ��������, ������� ���� � ������ ������������
 long amount=vector_TextureEnabledIndex.size(); 
 TextureList_Array=new GLuint[amount];
 glGenTextures(amount,TextureList_Array);
 for(n=0;n<amount;n++)
 {
  fseek(file,TextureOffsetList[vector_TextureEnabledIndex[n]],0);
  long size;
  GLfloat *TextureData;
  long ColorMode=LoadChar(file);
  if (ColorMode==1)//256 ������
  {
   for(long m=0;m<256;m++)
   {
    R[m]=(unsigned char)LoadChar(file);
    G[m]=(unsigned char)LoadChar(file);
    B[m]=(unsigned char)LoadChar(file);
   }
   size=(unsigned long)LoadShort(file);
   TextureData=new GLfloat[size*size*3];
   for(long x=0;x<size;x++)
   {
    for(long y=0;y<size;y++)
    {
     long byte=(unsigned char)LoadChar(file);
     TextureData[(x*size+y)*3]=(float)((float)R[byte]/255.0);
     TextureData[(x*size+y)*3+1]=(float)((float)G[byte]/255.0);
     TextureData[(x*size+y)*3+2]=(float)((float)B[byte]/255.0);
    }
   }
  }
  if (ColorMode==2)//RGB �����
  {
   size=(unsigned long)LoadShort(file);
   TextureData=new GLfloat[size*size*3];
   for(long x=0;x<size;x++)
   {
    for(long y=0;y<size;y++)
    {
     float r=(float)((unsigned char)LoadChar(file));
     float g=(float)((unsigned char)LoadChar(file));
     float b=(float)((unsigned char)LoadChar(file));
     TextureData[(x*size+y)*3]=(float)(r/255.0);
     TextureData[(x*size+y)*3+1]=(float)(g/255.0);
     TextureData[(x*size+y)*3+2]=(float)(b/255.0);
    }
   }
  }
  //��������� � � OpenGL
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glBindTexture(GL_TEXTURE_2D,TextureList_Array[n]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  //�������� ������ ��������
  gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,size,size,GL_RGB,GL_FLOAT,TextureData);
  delete(TextureData);
 }
 fclose(file);
 delete(TextureOffsetList);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//������� �������� � �������� texture_index �� ������ ������������
//----------------------------------------------------------------------------------------------------
bool CRenderTexture::SelectTexture(long texture_index)
{
 if (vector_TextureEnabledIndex.size()<=texture_index) return(false);//��������� ����� ��� �������� �� ���������
 glBindTexture(GL_TEXTURE_2D,TextureList_Array[texture_index]);
 return(true);
}
