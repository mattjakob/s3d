/*	image.h - image definitions	*/

#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

#define IMG_MONOCOL 0
#define IMG_MAPPCOL 1
#define IMG_TRUECOL 2

typedef unsigned char Byte;

typedef struct Bcolor {
  Byte z, y, x;
} Bcolor;

typedef struct Image {
  int w, h;
  unsigned int maxval;
  Bcolor *c;
} Image;


Image *img_init(int type, int w, int h);
void  img_free(Image *i);
void  img_clear(Image *i, Color c);

Image *img_read(char *fname);
void  img_write(Image *i, char *fname, int cflag);

void  img_putc(Image *i, int u, int v, Color c);
Color img_getc(Image *i, int u, int v);

#endif




