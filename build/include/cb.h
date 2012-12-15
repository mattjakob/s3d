#ifndef _GCB_H
#define _GCB_H

typedef int  Callback(char* e, real x, real y, void* p);

void gpmainloop(void);
Callback* gpregister(char* s, Callback* f, void* d);

#endif
