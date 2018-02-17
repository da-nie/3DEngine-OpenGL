#ifndef CFORM_H
#define CFORM_H
 
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "libext.h"
 
#include "common.h"
#include "copengl.h"
#include "cphysicengine.h"
#include "c3dengine.h"
#include "cplayer.h"
 
class CForm
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  COpenGL cOpenGL;
  C3DEngine c3DEngine;
  CPlayer cPlayer;
  long Tick;
  //-----------------------------------------------------------
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Update(void);
  void ExecuteOpenGL(void);
};
 
void CForm_Register(HINSTANCE hInstance);
LONG WINAPI CForm_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
 
#endif;
