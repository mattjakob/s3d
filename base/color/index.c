#include "color.h"

#define MASK_BITS(n) ((01 << (n))-1)

int rgb_to_index(Color c, int nr, int ng, int nb)
{
  unsigned int r = CLAMP(RED(c), 0, 255);
  unsigned int g = CLAMP(GRN(c), 0, 255);
  unsigned int b = CLAMP(BLU(c), 0, 255);
  
  r = (r >> (8 - nr)) & MASK_BITS(nr); 
  g = (g >> (8 - ng)) & MASK_BITS(ng); 
  b = (b >> (8 - nb)) & MASK_BITS(nb); 

  return ((r << (ng + nb)) | (g << nb) | b);
  
}

Color index_to_rgb(int k, int nr, int ng, int nb)
{
  unsigned int r, g, b;
  r = ((k >> (ng + nb)) & MASK_BITS(nr)) << (8 - nr);
  g = ((k >> (nb)) & MASK_BITS(ng)) << (8 - ng);
  b = ((k) & MASK_BITS(nb)) << (8 - nb);

  return c_make(r, g, b);
}
