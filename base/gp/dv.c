/*
* DV SDL + OpenGL
* lvelho@impa.br
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __APPLE__
#include <malloc.h>
#endif

#include <math.h>

#include "SDL.h"
#include "SDL_opengl.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define HAVE_OPENGL

#include "defs.h"
#include "gp.h"

#define vector(n,t)     ( (t*) malloc((n)*sizeof(t)) )
#define revector(p,n)   ( (void*) realloc(p,(n)*sizeof(*p)) )

#define IDLE            SDL_USEREVENT

typedef struct fcolor { 
  float r, g, b; 
} fcolor;


static Box      dv;
static int      bpp = 16;
static char     *dvsize = NULL;
static int      doublebuffermode=0;
static int      color=1;
static real     marksize=5;
static char*    marktype=".";
static fcolor*  colormap;
static int      colormapsize=256;
static int      polymode=0;
static int      points=0;
static real     wsize=1;

static int debug = FALSE;

static SDL_Surface      *screen = NULL;
static SDL_Cursor*      waitcursor = 0;
static SDL_Cursor*      closecursor = 0;
static SDL_Cursor*      defaultcursor = 0;

static void waitinput   (SDL_Cursor *cursor);
static int ParseGeometry(const char* string, int* x, int* y, unsigned int* width, unsigned int* height);

extern void glStrokeCharacter( int character );


static void setup_sdl(int  width, int height, char * wname) 
{
  int rgb_size[3];
  unsigned int flags;
 
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  /* Initialize the display */
  bpp = ( SDL_GetVideoInfo()->vfmt->BitsPerPixel <= 8 )? 8 : 16;
  switch (bpp) {
  case 8:
    rgb_size[0] = rgb_size[1] = 3; rgb_size[2] = 2;
    break;
  case 15:
  case 16:
    rgb_size[0] = rgb_size[1] = rgb_size[2] = 5;
    break;
  default:
    rgb_size[0] = rgb_size[1] = rgb_size[2] = 8;
    break;
  }
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, rgb_size[0] );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, rgb_size[1] );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, rgb_size[2] );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, doublebuffermode );
  flags = SDL_OPENGL | SDL_HWSURFACE | ((doublebuffermode)? SDL_DOUBLEBUF : 0);

  SDL_WM_SetCaption( wname, NULL );
  if ((screen = SDL_SetVideoMode(width, height, bpp, flags )) == 0 ) { //  | SDL_RESIZABLE
    fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
    exit(1);
  }
  defaultcursor = closecursor = waitcursor = SDL_GetCursor();
}

setup_dv(int width, int height)
{
  dv.xmin=0;
  dv.xmax=width;
  dv.ymin=0;
  dv.ymax=height;
  dv.xu=width;           
  dv.yu=height;
}


Box* dvopen(char* name, int width, int height)
{
  setup_sdl(width, height, name);
  setup_dv(width, height);

  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST );
  glViewport(0, 0, width, height);
  dvwindow(0, width, 0, height);

  if ((colormap=vector(colormapsize,fcolor)) == NULL)
    { fprintf(stderr, "GP: unable to alloc memory\n"); exit(-1); }
  if (colormapsize >= 2) {
    dvrgb(0, 1.,1.,1.);
    dvrgb(1, 0.,0.,0.);
  } else {
    fprintf(stderr,"GP colormap error (%d)\n", colormapsize);
  }
  glClear(GL_COLOR_BUFFER_BIT);
  return &dv;
}

void dvclose(int wait)
{
 if (wait) 
   waitinput(closecursor);
 SDL_Quit();
}

real dvwindow(real xmin, real xmax, real ymin, real ymax)
{
  wsize = MAX((xmax-xmin), (ymax-ymin));
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho((GLdouble)(xmin), (GLdouble)(xmax), (GLdouble)(ymin), (GLdouble)(ymax), -1.0, 1.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
}

real dvviewport(real xmin, real xmax, real ymin, real ymax)
{
  glViewport(xmin*dv.xmax, ymin*dv.ymax, (xmax-xmin)*dv.xmax, (ymax-ymin)*dv.ymax);
}

void dvclear(int wait)
{
 if (wait) 
   waitinput(waitcursor);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void dvflush(void)
{
  glFlush();
}

void dvwait(int t)
{
 void usleep(unsigned);                 /* sleep microseconds */
 glFlush();
 if (t>=0)
#ifdef WIN32
   Sleep(t);
#else
   usleep(1000*t);                      /* sleep t miliseconds */
#endif
 else
  waitinput(waitcursor);
}

int dvrgb(int c, real r, real g, real b)
{
  if (c>=0 && c<colormapsize) {
    colormap[c].r = r;
    colormap[c].g = g;
    colormap[c].b = b;
  }
  if (c==0)                     /* color 0 is background */
    glClearColor(colormap[c].r, colormap[c].g, colormap[c].b, 0.0);
  else if (c < 0)               /* immediate mode */
    glColor3f((GLfloat)(r), (GLfloat)(g), (GLfloat)(b));
  return c;
}

int dvcolor(int c)
{
 if (c<0 || c>=colormapsize) {
   if (c==1)
     glColor3f(0.0, 0.0, 0.0);
   return -colormapsize;
 } else {
   int old=color;
   color=c;
   colormap[c];
   glColor3f((GLfloat)(colormap[c].r), (GLfloat)(colormap[c].g), (GLfloat)(colormap[c].b));
   return old;
 }
}

void dvmark(int size, char* mark)
{
 if (size>0) marksize=size;
 if (mark!=NULL && *mark!=0) marktype=mark;
}

void dvline(real x1, real y1, real x2, real y2)
{
  glBegin(GL_LINES);
  glVertex2d((GLdouble)(x1), (GLdouble)(y1)); 
  glVertex2d((GLdouble)(x2), (GLdouble)(y2)); 
  glEnd();
}

void dvbox(real xmin, real xmax, real ymin, real ymax)
{
  glRectd((GLdouble)(xmin), (GLdouble)(ymin), (GLdouble)(xmax), (GLdouble)(ymax));
}


void dvtext(real x, real y, char* s, char* m)
{
 char *p;
 real size=0.075*marksize*wsize/dv.xmax;
 glPushMatrix();
 glTranslatef(x, y, 0);
 glScaled((GLdouble)size,(GLdouble)size,(GLdouble)size);
 for (p = s; *p; p++) {
   glStrokeCharacter(*p);
 }
 glPopMatrix();
}

void dvplot(real x, real y)
{
 real s=marksize*wsize/dv.xmax;
 glRectd((GLdouble)(x-s), (GLdouble)(y-s), (GLdouble)(x+s), (GLdouble)(y+s));
}

void dvbegin(int mode)
{
  int glmode;
  polymode=mode;
  points=0;
  switch (polymode)  {
  case 'p':                             /* closed polygonal line */
    glmode = GL_LINE_LOOP; break;
  case 'l':                             /* open polygonal line */
    glmode = GL_LINE_STRIP; break;
  case 'f':                             /* filled polygon */
    glmode = GL_POLYGON; break;
  case 'm':                             /* polymarker (only dots) */
    glmode = GL_POINTS; break;
  }
  glBegin(glmode);
}

int dvpoint(real x, real y)
{
  glVertex2d((GLdouble)(x), (GLdouble)(y));
  return points++;
}

void dvend(void)
{
  glEnd();
  polymode=0;
  points=0;
}

char* dvevent(int wait, int* x, int* y)
{
  static char report[]="m123+SCM00000";
  unsigned int button, status, state=0;
  char* r=report;
  SDL_Event event;

  event.type = IDLE;
  if (wait)
    status = SDL_WaitEvent(&event);
  else
    status = SDL_PollEvent(&event);

  SDL_GetMouseState(x, y);
  *y=dv.ymax - *y;

  switch(event.type) {
  case SDL_ACTIVEEVENT:
    if (debug) {
      if (event.active.state & SDL_APPMOUSEFOCUS) {
        if (event.active.gain) {
          printf("Mouse focus gained\n");
        } else {
          printf("Mouse focus lost\n");
        }
      }
      if (event.active.state & SDL_APPINPUTFOCUS) {
        if (event.active.gain) {
          printf("Input focus gained\n");
        } else {
          printf("Input focus lost\n");
        }
      }
      if (event.active.state & SDL_APPACTIVE) {
        if (event.active.gain) {
          printf("Application restored\n");
        } else {
          printf("Application iconified\n");
        }
      }
    }
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    if (debug) {
      printf ("Key pressed / released:\n");
      printf ("       SDL sym: %i\n",event.key.keysym.sym);
      printf ("       modifiers: %i\n",event.key.keysym.mod);
      printf ("       unicode: %i (if enabled with SDL_EnableUNICODE)\n",event.key.keysym.unicode);
    }
    report[1]=0;
    state=event.key.keysym.mod;
    *r++='k';
    *r++=event.key.keysym.sym;
    *r++=(event.type==SDL_KEYDOWN) ? '+' : '-';
    break;
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
    if (debug) {
      printf ("Mouse button %i ",event.button.button);
      printf ("pressed / released with mouse at (%i,%i)\n",event.button.x,event.button.y);
    }
    state=event.button.state;
    *x=event.button.x;
    *y=event.button.y;
    *y=dv.ymax - *y;
    *r++='b';
    *r++='0'+event.button.button; // FIX
    *r++=(event.type==SDL_MOUSEBUTTONDOWN) ? '+' : '-';
    break;
  case SDL_MOUSEMOTION:
    if (debug) {
      printf ("Mouse moved to: (%i,%i) ", event.motion.x, event.motion.y);
      printf ("change: (%i,%i)\n", event.motion.xrel, event.motion.yrel);
      printf ("       button state: %i\n",event.motion.state);
    }
    state=event.motion.state;
    button = (state & SDL_BUTTON(1))? 1 : (state & SDL_BUTTON(2))? 2 : (state & SDL_BUTTON(3))? 3 : 0;
    *x=event.motion.x;
    *y=event.motion.y;
    *y=dv.ymax - *y;
    *r++='m';
    *r++='0'+ button; // FIX
    *r++='+';
    break;
  case IDLE:   // SDL_USEREVENT:
    if (debug) {
      printf ("User event:\n");
      printf ("       code:  %i\n",event.user.code);
      printf ("       data1: %p\n",event.user.data1);
      printf ("       data2: %p\n",event.user.data2);
    }
    *r++='i';
    *r++='+';
    break;
  case SDL_VIDEOEXPOSE:
    if (debug)
      printf ("Window exposed\n");
    *r++='r';
    *r++='+';   /* signal last expose */
    break;
  case SDL_VIDEORESIZE: /* does not work... */
    if (debug)
      printf ("Window resized to: (%i,%i)\n",event.resize.w, event.resize.h);
    if (SDL_SetVideoMode(event.resize.w, event.resize.h, bpp, SDL_OPENGL | SDL_RESIZABLE) == 0 ) {
      fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
      exit(1);
    }
    if (event.resize.w != dv.xmax  || event.resize.h != dv.ymax) {
      *x=event.resize.w;
      *y=event.resize.h;
      *y=dv.ymax - *y;
      *r++='s';
      setup_dv(event.resize.w, event.resize.h);
      glViewport(0, 0, event.resize.w, event.resize.h);
      glColor3f(1.0, 1.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
    break;
  case SDL_SYSWMEVENT:
    if (debug)
      printf ("Window manager event\n");
    break;
  case SDL_QUIT:
    if (debug)
      printf ("Request to quit\n");
    break;
  default:
    ;
  }
  state = SDL_GetModState();
  if (state & KMOD_SHIFT) *r++='S';
  if (state & KMOD_CTRL) *r++='C';
  if (state & KMOD_META ) *r++='M';
  *r++=0;
  return report;
}

static void waitinput(SDL_Cursor *cursor)
{
  int nev;
  SDL_Event event;
  SDL_SetCursor(cursor);
  do {
    SDL_PumpEvents();
    nev=SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, (SDL_EVENTMASK (SDL_KEYUP) | SDL_EVENTMASK (SDL_MOUSEBUTTONUP)));
  }  while (nev <= 0);
  SDL_SetCursor(defaultcursor);
}

void dvsetdoublebuffer(int onoff)
{
  if (screen != NULL) 
    fprintf(stderr, "SDL DV: cannot set doublebuffer mode after gpopen\n");
  else
    doublebuffermode = onoff;
}

void dvswapbuffers(void)
{
  if (doublebuffermode) {
    SDL_GL_SwapBuffers();
    SDL_Flip(screen);
  }
  glFlush();
}

