#include "image.h"
#include "rasterfile.h"

/* sunras */

void ras_header(struct rasterfile *h, Image *i, int cflag)
{
  h->ras_magic = RAS_MAGIC;
  h->ras_width = i->w;
  h->ras_height = i->h;
  h->ras_depth = (img_type(i) == IMG_TRUECOL)? 24 : 8;
  h->ras_length = i->w * i->h;
  h->ras_type = (cflag)? RT_SIMPLE_RLE : RT_STANDARD;
  h->ras_maptype = (img_type(i) == IMG_MAPPCOL)? RMT_EQUAL_RGB : RMT_NONE;
  h->ras_maplength = (img_type(i) == IMG_MAPPCOL)? 0 : 0;
}

void read_sunheader(int fd, struct rasterfile *h)
{
  read_sun_long(&(h->ras_magic), fd);
  read_sun_long(&(h->ras_width), fd);
  read_sun_long(&(h->ras_height), fd);
  read_sun_long(&(h->ras_depth), fd);
  read_sun_long(&(h->ras_length), fd);
  read_sun_long(&(h->ras_type), fd);
  read_sun_long(&(h->ras_maptype), fd);
  read_sun_long(&(h->ras_maplength), fd);
}

void write_sunheader(int fd, struct rasterfile *h)
{
  write_sun_long(h->ras_magic, fd);
  write_sun_long(h->ras_width, fd);
  write_sun_long(h->ras_height, fd);
  write_sun_long(h->ras_depth, fd);
  write_sun_long(h->ras_length, fd);
  write_sun_long(h->ras_type, fd);
  write_sun_long(h->ras_maptype, fd);
  write_sun_long(h->ras_maplength, fd);
}

void read_sun_long(int *l, int fd)
{
  unsigned char c0, c1, c2, c3;

  read(fd,&c0,1); read(fd,&c1,1); read(fd,&c2,1); read(fd,&c3,1);

  *l = (((unsigned int) c0 & 0xff) << 24) |
       (((unsigned int) c1 & 0xff) << 16) |
       (((unsigned int) c2 & 0xff) <<  8) |
       (((unsigned int) c3 & 0xff));
}

void write_sun_long(unsigned int l, int fd)
{
    unsigned char c;
    c = ((l >> 24) & 0xff); write(fd, &c, 1);
    c = ((l >> 16) & 0xff); write(fd, &c, 1);
    c = ((l >> 8) & 0xff); write(fd, &c, 1);
    c = (l & 0xff); write(fd, &c, 1);
}

void sunras_read(int fd, int d, int w, int h, void *buf)
{
  int i, lsize, padline;
  char pad[1], *bp;

  lsize = (w * d)/8;
  padline = ((w * d) % 16)? TRUE : FALSE;
  for (i = 0, bp = buf; i < h; i++, bp += lsize) {
    read(fd, bp, lsize);
    if (padline) read(fd, &pad, 1);
  }
}

void sunras_write(int fd, int d, int w, int h, void *buf)
{
  int i, lsize, padline;
  char pad[1], *bp;

  lsize = (w * d)/8;
  padline = ((w * d) % 16)? TRUE : FALSE;
  for (i = 0, bp = buf; i < h; i++, bp += lsize) {
    write(fd, bp, lsize);
    if (padline) write(fd, &pad, 1);
  }
}
