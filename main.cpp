#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
 
 
#include "cform.h"
 
extern CForm cForm;

extern bool DriverIsActive;
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 MSG msg;
 DriverIsActive=false;
 CForm_Register(hInstance);
 SetCursorPos(WIDTH_SCREEN/2,HEIGHT_SCREEN/2);
 ShowCursor(FALSE);
 //поменяем видеорежим
 DEVMODE dev;
 memset(&dev,0,sizeof(dev));
 dev.dmSize=sizeof(dev);
 dev.dmBitsPerPel=32;
 dev.dmPelsWidth=WIDTH_SCREEN;
 dev.dmPelsHeight=HEIGHT_SCREEN;
 dev.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
 ChangeDisplaySettings(&dev,0);
  
 LARGE_INTEGER start_time;
 LARGE_INTEGER current_time;
 LARGE_INTEGER CounterFrequency;
 QueryPerformanceFrequency(&CounterFrequency);
 double d_CounterFrequency=(double)CounterFrequency.QuadPart;
 QueryPerformanceCounter(&start_time);
 double d_start_time=(double)start_time.QuadPart;
 while(1)
 {
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
   if (msg.message==WM_QUIT) break;
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  if (msg.message==WM_QUIT) break;
  while(1)
  {
   QueryPerformanceCounter(&current_time);
   double d_current_time=(double)current_time.QuadPart;
   double delta_time=d_current_time-d_start_time;
   if (delta_time<d_CounterFrequency/FPS2) continue;
   break;
  }
  QueryPerformanceCounter(&start_time);
  d_start_time=(double)start_time.QuadPart;
  if (msg.message==WM_QUIT) break;
  if (DriverIsActive==true) cForm.Update();
 }
 ShowCursor(TRUE);
 return(0);
}
 
