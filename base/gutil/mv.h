/*
* mv.h
* multiple viewports
* Luiz Henrique de Figueiredo
* 29 Dec 92
*/

#ifndef _MV_H
#define _MV_H

int	mvopen	(int n);
void	mvclose	(void);
void	mvwindow(int n, real xmin, real xmax, real ymin, real ymax);	
void	mvviewport(int n, real xmin, real xmax, real ymin, real ymax);
void	mvframe	(void);
void	mvclear	(int c);
int	mvact	(int n);
void	mvdiv	(int nx, int ny, real xmin, real xmax, real ymin, real ymax);
void	mvmake	(int nx, int ny);
char*	mvevent	(int wait, real* x, real* y, int* view);

typedef int   MvCallback(void* p, int v, real x, real y, char* e);

void mvmainloop(void);
MvCallback* mvregister(int v, char* s, MvCallback* f, void* d);

#endif
