#ifndef CRENDER_FRAGMENT_H
#define CRENDER_FRAGMENT_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>

#include "formats.h"
#include "libext.h"

#include <vector>
using namespace std;

//класс фрагментов
class CRenderFragment
{
 protected:
  bool LightingState[8];//состояние источников света (true - источник включён)
  GLuint List;//номер списка для отрисовки фрагмента
  long Vertex;//число вершин полигона фрагмента
  //все координаты нужны только для генерации списка
  struct SVertex
  {
   //координаты полигона
   float X;
   float Y;
   float Z;
   //текстурные координаты полигона
   float TU;
   float TV;
  };
  vector<SVertex> vector_SVertex;//координаты вершин фрагмента
  //нормаль фрагмента
  float N_X;
  float N_Y;
  float N_Z;
 public:
  CRenderFragment(void);//конструктор
  ~CRenderFragment(void);//деструктор
 public:
  void Draw(void);//нарисовать фрагмент
  void Load(FILE *File);//загрузить фрагмент
  void Release(void);//удалить фрагмент
  void SetNormal(float nx,float ny,float nz);//задать нормаль
  void CreateList(long &list);//создать список  с номером list
};
#endif
