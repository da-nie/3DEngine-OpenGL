#include "copengl.h"
 
int COpenGL::SetDCPixelFormat(HDC hdc)
{
 static PIXELFORMATDESCRIPTOR pfd =
 {
  sizeof (PIXELFORMATDESCRIPTOR),                        // sizeof this structure
  1,                                                     // version number
  PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,// flags
  PFD_TYPE_RGBA,                                         // RGBA pixel values
  32,                                                    // 32-bit color
  0,0,0,0,0,0,                                           // don't care about these
  0,0,                                                   // no alpha buffer
  0,0,0,0,0,                                             // no accumulation buffer
  32,                                                    // 32-bit depth buffer
  0,                                                     // no stencil buffer
  0,                                                     // no auxiliary buffers
  PFD_MAIN_PLANE,                                        // layer type
  0,                                                     // reserved (must be 0)
  0,0,0                                                  // no layer masks
 };
 int pixelFormat;
 pixelFormat=ChoosePixelFormat(hdc,&pfd);
 SetPixelFormat(hdc,pixelFormat,&pfd);
 DescribePixelFormat(hdc,pixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
 if (pfd.dwFlags&PFD_NEED_PALETTE) return(1);
 return(0);
}
void COpenGL::CreateContext(HDC hdc)
{
 hrc=wglCreateContext(hdc);
 //отключаем вертикальную синхронизацию 
 wglMakeCurrent(hdc,hrc);
 typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
 PFNWGLSWAPINTERVALEXTPROC wglSwapInterval=NULL;
 wglSwapInterval=(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT"); 
 wglSwapInterval(0);
 wglMakeCurrent(NULL,NULL);
}
void COpenGL::DeleteContext(void)
{
 wglDeleteContext(hrc);
}
void COpenGL::EnableMakeCurrent(HDC hdc)
{
 wglMakeCurrent(hdc,hrc);
}
void COpenGL::DisableMakeCurrent(void)
{
 wglMakeCurrent(NULL,NULL);
}
void COpenGL::SetProjectMatrix(int dx,int dy,float angle)
{
 double aspect=(double)(dx)/(double)(dy);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(angle,aspect,1,1000000);
 glViewport(0,0,dx,dy);
}
 
