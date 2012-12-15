#ifdef WIN32
#define CYGWIN
#endif

#ifdef CYGWIN
#include <fcntl.h>
#endif

#include "image.h"
#include "pam.h"


#define PIX_MIN 0
#define PIX_MAX 255

#define PIXRED(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].x
#define PIXGRN(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].y
#define PIXBLU(I,U,V) I->c[U + (((I->h - 1) - (V)) * I->w)].z


Image *img_init(int type, int w, int h)
{
  Image *i = NEWSTRUCT(Image);
  
  i->w = w; i->h = h;
  i->maxval = 255;
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
  FILE *fp, *fp2;
  int row, col, cols, rows;
  pixval maxval;
  pixel **pixels;
  Image *i;
  
  fp =  (strcmp("stdin", fname) == 0)? stdin : fopen(fname, "rb");
  pixels = ppm_readppm(fp, &cols, &rows, &maxval);
  i = img_init(0, cols, rows);
  i->maxval = maxval;
  for ( row = 0; row < rows; ++row ) {
    for ( col = 0; col < cols; ++col) {
      pixel const p = pixels[row][col];
      img_putc(i, col, rows-row-1, c_make(PPM_GETR(p), PPM_GETG(p), PPM_GETB(p)));
    }
  }
  ppm_freearray(pixels, rows);
  fclose(fp);
  return i;
}


void img_write(Image *i, char *fname, int cflag)
{
  FILE *fp;
  int row, col;
  pixval maxval;
  pixel **pixels;

  fp = (strcmp("stdout", fname) == 0)? stdout : fopen(fname, "wb");
  pixels = ppm_allocarray(i->w, i->h);
  if (!pixels)
    error("ppm image write: failed to alloc");
  for ( row = 0; row < i->h; ++row ) {
    for ( col = 0; col < i->w; ++col) {
      Color c = img_getc(i, col, i->h - row - 1);
      pixel p = pixels[row][col];
      (pixels[row][col]).r  = RED(c);
      (pixels[row][col]).g  = GRN(c);
      (pixels[row][col]).b  = BLU(c);
    }
  }
  ppm_writeppm(fp, pixels, i->w, i->h, i->maxval, TRUE);
  ppm_freearray(pixels, i->h);
  if  (strcmp("stdout", fname) != 0) 
    fclose(fp);
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
