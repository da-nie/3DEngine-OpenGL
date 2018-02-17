#include "cform.h"
 
CForm cForm;
bool DriverIsActive;
extern float Lighting_Ambient_R;
extern float Lighting_Ambient_G;
extern float Lighting_Ambient_B; 
extern double Lighting_Constant_Attenuation;
extern double Lighting_Linear_Attenuation;
extern double Lighting_Quadric_Attenuation;

extern CPhysicEngine cPhysicEngine;

//------------------------------------------------------------------------------
void CForm_Register(HINSTANCE hInstance)
{
 WNDCLASS wc;
 wc.style=CS_HREDRAW|CS_VREDRAW;
 wc.cbClsExtra=0;
 wc.cbWndExtra=0;
 wc.hInstance=hInstance;
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="CForm";
 wc.lpfnWndProc=(WNDPROC)CForm_wndProc;
 RegisterClass(&wc);
 HWND hWnd=GetDesktopWindow();
 HWND hWndS=CreateWindow("CForm","3DEngine",WS_POPUP|WS_VISIBLE,0,0,WIDTH_SCREEN,HEIGHT_SCREEN,hWnd,0,hInstance,NULL);
 SetWindowPos(hWndS,HWND_TOPMOST,0,0,0,SWP_NOMOVE|SWP_NOREDRAW,SWP_NOSIZE);
}
//------------------------------------------------------------------------------
LONG WINAPI CForm_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   cForm.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   cForm.Destroy(hWnd,wParam,lParam);
   PostQuitMessage(0);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void CForm::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{ 
 hWnd=hWnds;
 HDC hdc=GetDC(hWnd);
 if (cOpenGL.SetDCPixelFormat(hdc)==1)
 {
  MessageBox(hWnd,"Не удалось активировать OpenGL.","Ошибка",MB_OK);
  ReleaseDC(hWnd,hdc);
  DestroyWindow(hWnd);
  return;
 }
 cOpenGL.CreateContext(hdc);
 cOpenGL.EnableMakeCurrent(hdc);
 cOpenGL.SetProjectMatrix(WIDTH_SCREEN,HEIGHT_SCREEN,50);
 glEnable(GL_DEPTH_TEST);
 glDepthFunc(GL_LEQUAL);
 glDisable(GL_DITHER);
 glShadeModel(GL_SMOOTH);
 glEnable(GL_CULL_FACE);
 glFrontFace(GL_CW);
 glCullFace(GL_BACK);
 glEnableClientState(GL_NORMAL_ARRAY);
 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_TEXTURE_COORD_ARRAY);

 //glHint(GL_POLYGON_SMOOTH_HINT,GL_FASTEST);//а на ati не тормозит при NICEST (странно ...)
 //glEnable(GL_POLYGON_SMOOTH);
 glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
 glEnable(GL_TEXTURE_2D);
 glMatrixMode(GL_TEXTURE);
 glLoadIdentity();
 c3DEngine.LoadStage("1.stg");
 glColor3f(1,1,1);
 glClearColor(0,0,0,0);
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glEnable(GL_LIGHTING);
 float m_ambient[]={1,1,1,1};
 float m_diffuse[]={1,1,1,1};
 float m_specular[]={1,1,1,1};
 float m_emission[]={0,0,0,1};
 float m_shininess[]={100};
 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_ambient);
 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_diffuse);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_specular);
 glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,m_emission);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,m_shininess);
 float global_ambient[]={Lighting_Ambient_R,Lighting_Ambient_G,Lighting_Ambient_B};
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient);
 // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
 //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
 for(int n=0;n<8;n++)
 {
  float l_ambient[4]={0,0,0,1};
  float l_specular[4]={0,0,0,1};
  glLightfv(GL_LIGHT0+n,GL_AMBIENT,l_ambient);
  glLightfv(GL_LIGHT0+n,GL_SPECULAR,l_specular);
 }
 cOpenGL.DisableMakeCurrent();
 ReleaseDC(hWnd,hdc);
 cPhysicEngine.SetCharacterInMap(1);
 cPlayer.LoadStartPos("1.stg");
 cPlayer.SetCharacterNumber(0);
 DriverIsActive=true;
 Tick=0;
}
void CForm::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 DriverIsActive=false;
 HDC hdc=GetDC(hWnd);
 cOpenGL.EnableMakeCurrent(hdc);
 c3DEngine.DeleteStage();
 cOpenGL.DisableMakeCurrent();
 ReleaseDC(hWnd,hdc);
 cOpenGL.DeleteContext();
 ChangeDisplaySettings(NULL,0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void CForm::Update(void)
{ 
 //проверяем управление
 if (GetAsyncKeyState(VK_LEFT)&32768) cPlayer.RotateLeft();
 if (GetAsyncKeyState(VK_RIGHT)&32768) cPlayer.RotateRight();
 if (GetAsyncKeyState(VK_UP)&32768) cPlayer.MoveUp();
 if (GetAsyncKeyState(VK_DOWN)&32768) cPlayer.MoveDown();
 if (GetAsyncKeyState(VK_END)&32768) cPlayer.CenterViewZX();
 if (GetAsyncKeyState(VK_DELETE)&32768) cPlayer.StepLeft();
 if (GetAsyncKeyState(VK_NEXT)&32768) cPlayer.StepRight();
 if (GetAsyncKeyState(VK_SPACE)&32768) cPlayer.Activate();
 if (GetAsyncKeyState(VK_F1)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 }
 if (GetAsyncKeyState(VK_F2)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 }
 if (GetAsyncKeyState(VK_F3)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glDisable(GL_TEXTURE_2D);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 }
 if (GetAsyncKeyState(VK_F4)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glEnable(GL_TEXTURE_2D);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 }
 if (GetAsyncKeyState(VK_F5)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glDisable(GL_LIGHTING);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 }
 if (GetAsyncKeyState(VK_F6)&32768)
 {
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  glEnable(GL_LIGHTING);
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
 } 
 if (GetAsyncKeyState(VK_ESCAPE)&32768)
 {
  DestroyWindow(hWnd);
  return;
 }
 if (GetAsyncKeyState(VK_RETURN)&32768)
 {
  SYSTEMTIME time;
  GetSystemTime(&time);
  float time1=(float)(time.wSecond+time.wMinute*60+time.wHour*60*60+time.wMilliseconds/1000.0);
  SCharacter sCharacter;
  cPlayer.GetPlayerCharacter(&sCharacter);
  HDC hdc=GetDC(hWnd);
  cOpenGL.EnableMakeCurrent(hdc);
  for(int n=0;n<3600;n++)
  {
   sCharacter.AngleXY++;
   if (sCharacter.AngleXY>360) sCharacter.AngleXY-=360;
   c3DEngine.Draw(&sCharacter);
   SwapBuffers(hdc);
  }
  cOpenGL.DisableMakeCurrent();
  ReleaseDC(hWnd,hdc);
  GetSystemTime(&time);
  float time2=(float)(time.wSecond+time.wMinute*60+time.wHour*60*60+time.wMilliseconds/1000.0);
  float fps=(float)(3600.0/(time2-time1));
  FILE *file=fopen("fps.txt","w+b");
  fprintf(file,"Число кадров в секунду:%f",fps);
  fclose(file);
 }
 POINT Cursor;
 GetCursorPos(&Cursor);
 cPlayer.SetLookParameter((float)((Cursor.x-WIDTH_SCREEN/2)/7.0),(float)((Cursor.y-HEIGHT_SCREEN/2)/10.0));
 SetCursorPos(WIDTH_SCREEN/2,HEIGHT_SCREEN/2);
  
 cPlayer.Processing();
 cPhysicEngine.Processing();
 Tick++;
 c3DEngine.Animate(Tick);
 Tick%=10;
 c3DEngine.AnimateScroll();
 HDC hdc=GetDC(hWnd);
 cOpenGL.EnableMakeCurrent(hdc);
 SCharacter sCharacter;
 cPlayer.GetPlayerCharacter(&sCharacter);
 c3DEngine.Draw(&sCharacter);
 SwapBuffers(hdc);
 cOpenGL.DisableMakeCurrent();
 ReleaseDC(hWnd,hdc);
}
 
