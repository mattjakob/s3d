#ifdef WIN32
#define CYGWIN
#endif

#ifdef CYGWIN
#include <fcntl.h>
#endif

#include "image.h"
#include "rasterfile.h"


#define IMG_RASTYPE(h) \
  ((h.ras_depth == 24)? IMG_TRUECOL : \
   (h.ras_depth == 8 && h.ras_maptype == RMT_EQUAL_RGB)? IMG_MAPPCOL : \
   IMG_MONOCOL)


#define PIX_MIN 0
#define PIX_MAX 255

#define PIXRED(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].x
#define PIXGRN(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].y
#define PIXBLU(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].z


Image *img_init(int type, int w, int h)
{
  Image *i = NEWSTRUCT(Image);
  
  i->w = w; i->h = h;
  i->c = NEWTARRAY(w*h, Bcolor);
  img_clear(i, C_BLACK);
  return i;
}


void img_clear(Image *i, Color c)
{
  int u,v;
  for (v = 0; v < i->h; v++)
    for (u = 0; u < i->w; u++)
      img_putc(i,u,v,c);
}


Image *img_read(char *fname)
{
  struct rasterfile h;
  int fd;
  Image *i;
  
  fd =  (strcmp("stdin", fname) == 0)? 0 : eopen(fname, 0);
#ifdef CYGWIN
  setmode(fd, O_BINARY);
#endif

  read_sunheader(fd, &h);
  if (h.ras_magic != RAS_MAGIC)
    error("(img_read) wrong format");
  i = img_init(IMG_RASTYPE(h), h.ras_width, h.ras_height);

  switch (h.ras_type) {
  case RT_FORMAT_RGB:
  case RT_STANDARD: 
    sunras_read(fd, h.ras_depth, i->w, i->h, i->c); break;
  case RT_SIMPLE_RLE:
  default: 
    error("(img_read) unknown format"); break;
  }
  close(fd);
  return i;
}


void img_write(Image *i, char *fname, int cflag)
{
  struct rasterfile h;
  int fd;

  fd = (strcmp("stdout", fname) == 0)? 1 : ecreat(fname, 0666);
#ifdef CYGWIN
  setmode(fd, O_BINARY);
#endif

  ras_header(&h, i, cflag);
  write_sunheader(fd, &h);

  switch (h.ras_type) {
  case RT_FORMAT_RGB:
    sunras_write(fd, h.ras_depth, i->w, i->h, i->c); break;
  case RT_STANDARD: 
  case RT_SIMPLE_RLE: 
    error("(img_read) unknown format"); break;
  }
  close(fd);
}


void img_putc(Image *i, int u, int v, Color c)
{
  if (u >= 0 && u < i->w && v >= 0 && v < i->h) {
    PIXRED(i,u,v) = CLAMP(RED(c), PIX_MIN, PIX_MAX); 
    PIXGRN(i,u,v) = CLAMP(GRN(c), PIX_MIN, PIX_MAX); 
    PIXBLU(i,u,v) = CLAMP(BLU(c), PIX_MIN, PIX_MAX);
  }
}

Color img_getc(Image *i, int u, int v)
{
  if (u >= 0 && u < i->w && v >= 0 && v < i->h)
    return c_make(PIXRED(i,u,v),PIXGRN(i,u,v),PIXBLU(i,u,v));
  else
    return C_BLACK;
}

void img_free(Image *i)
{
  efree(i->c); efree(i);
}
