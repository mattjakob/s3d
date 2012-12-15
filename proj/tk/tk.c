#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "laux.h"
#include "geom.h"
#include "gp.h"
#include "mv.h"
#include "tk.h"

// Local Variables

Widget **wa = NULL;
int wn = 0;
int wi = 0;

void tk_open(int n)
{
  int i;
  mvopen(n);
  wa = NEWARRAY(n, Widget *);
  for (i=0; i<n; i++)
    wa[i] = NULL;
  wn = n;
  wi = 0;
  mvregister(-1,"r",tk_redraw,NULL);
  gpflush();
}

void tk_close()
{
  efree(wa);
  wa = NULL; wn = wi = 0;
  mvclose();
}

void tk_mainloop()
{
  mvmainloop();
}

int  tk_redraw(void* p, int v, real x, real y, char* e)
{
  int i;
  fprintf(stderr, "redraw\n"); fflush(stderr);
  for (i=0; i<wi; i++) {
    switch (wa[i]->type) {
    case TK_BUTTON:
      button_draw(wa[i], 1); break;
    default:
      error("tk"); break;
    }
  }
  gpflush();
  return 0;
}

Widget* tk_widget(int type, real x, real y, int (*f)(), void *d)
{
  Widget *w = widget_new(type, x, y, 0.2, f);
  if (wi >= wn) 
    error("tk");
  w->id = wi++;
  wa[w->id] = w;
  mvwindow(w->id, 0, 1, 0, 1);
  mvviewport(w->id, w->xo, w->xo + w->xs, w->yo, w->yo + w->ys);
  switch (type) {
  case TK_BUTTON:
    button_make(w, d); break;
  default:
    error("tk"); break;
  }
  return w;
}

Widget* widget_new(int type, real x, real y, real s, int (*f)())
{
  Widget *w = NEWSTRUCT(Widget);
  w->id = -1;
  w->type = type;
  w->xo = x; w->yo = y;
  w->xs = w->ys = s;
  w->f = f;
  w->d = NULL;
  return w;
}

void button_make(Widget *w, char *s)
{
  mvregister(w->id,"b1+",button_pressed,w);
  mvregister(w->id,"b1-",button_released,w);
  w->d = s;
  button_draw(w, 1);
}

void button_draw(Widget *w, int posneg)
{
  char *label = w->d;
  int fg, bg;
  if (posneg) { 
    fg = 1; bg = 0; 
  } else { 
    fg = 0; bg = 1;  
  }
  mvact(w->id);
  gpcolor(fg);
  gpbox(0., 1., 0., 1.);
  gpcolor(bg);
  gptext(.2, .2, label, NULL); 
  mvframe();
  gpflush();
}

int  button_pressed(void* p, int v, real x, real y, char* e)
{
  button_draw(p, 0);
  return 0;
}

int  button_released(void* p, int v, real x, real y, char* e)
{
  Widget *w = p;
  button_draw(w, 1);
  return w->f();
}

