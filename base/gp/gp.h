/*
* gp.h
* a simple 2d graphics package
* Luiz Henrique de Figueiredo (lhf@visgraf.impa.br)
* modifications by Luiz Velho (lvelho@impa.br)
*/

#ifndef GP_H
#define GP_H

#include "defs.h"

#define real    double
#define Box     gpBox

typedef struct {
 real xmin;
 real xmax;
 real ymin;
 real ymax;
 real xu;
 real yu;
} Box;


real    gpopen          (char* name, int width, int height);
real    gpwindow        (real xmin, real xmax, real ymin, real ymax);
real    gpviewport      (real xmin, real xmax, real ymin, real ymax);
void    gpview          (real* x, real* y);
void    gpunview        (real* x, real* y);
void    gpmake          (void);
char*   gpevent         (int wait, real* x, real* y);

void    gpbegin         (int c);
#define gpbegin         dvbegin
void    gpend           (void);
#define gpend           dvend
void    gpclose         (int wait);
#define gpclose         dvclose
void    gpclear         (int wait);
#define gpclear         dvclear
void    gpflush         (void);
#define gpflush         dvflush
void    gpwait          (int t);
#define gpwait          dvwait
int     gprgb           (int c, real r, real g, real b);
#define gprgb           dvrgb
int     gpcolor         (int c);
#define gpcolor         dvcolor
void    gpmark          (int size, char* mark);
#define gpmark          dvmark
void    gptext          (real x, real y, char* s, char* mode);
#define gptext          dvtext
void    gpline          (real x1, real y1, real x2, real y2);
#define gpline          dvline
void    gpbox           (real xmin, real xmax, real ymin, real ymax);
#define gpbox          dvbox
void    gpplot          (real x, real y);
#define gpplot          dvplot
int     gppoint         (real x, real y);
#define gppoint         dvpoint

#define gpsetdoublebuffer dvsetdoublebuffer
#define gpswapbuffers   dvswapbuffers

/* device */

Box*    dvopen          (char* name, int width, int height);
void    dvclose         (int wait);
real    dvwindow        (real xmin, real xmax, real ymin, real ymax);
real    dvviewport      (real xmin, real xmax, real ymin, real ymax);
void    dvclear         (int wait);
void    dvflush         (void);
void    dvwait          (int t);
int     dvrgb           (int c, real r, real g, real b);
int     dvcolor         (int c);
void    dvmark          (int size, char* mark);
void    dvline          (real x1, real y1, real x2, real y2);
void    dvbox           (real xmin, real xmax, real ymin, real ymax);
void    dvtext          (real x, real y, char* s, char* mode);
void    dvplot          (real x, real y);
void    dvbegin         (int c);
int     dvpoint         (real x, real y);
void    dvend           (void);
char*   dvevent         (int wait, int* x, int* y);

void    dvsetdoublebuffer(int onoff);
void    dvswapbuffers   (void);


#ifndef rad
#define rad(a)          ((a)*(real)0.01745329252)
#endif

#ifndef WIN32
#ifdef __DARWIN_UNIX03
extern double round( double );
#else
#ifndef round 
#define round(x)        ((int)((x)+(real)0.5))
#endif
#endif
#endif

#ifndef min
#define min(x,y)        ( ((x)<(y)) ? (x) : (y) )
#endif

#ifndef max
#define max(x,y)        ( ((x)>(y)) ? (x) : (y) )
#endif

#endif /*  GP_H */


