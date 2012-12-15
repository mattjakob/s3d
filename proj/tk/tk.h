

typedef struct Widget {
  int id;
  int type;
  real xo, yo;
  real xs, ys;
  void* d;
  int (*f)();
} Widget;


Widget* widget_new(int type, real x, real y, real s, int (*f)());

void tk_open(int n);
void tk_close();
void tk_mainloop();
Widget* tk_widget(int type, real x, real y, int (*f)(), void *d);
int  tk_redraw(void* p, int v, real x, real y, char* e);

#define TK_BUTTON 1

void button_make(Widget *w, char *s);
void button_draw(Widget *w, int posneg);
int  button_pressed(void* p, int v, real x, real y, char* e);
int  button_released(void* p, int v, real x, real y, char* e);
