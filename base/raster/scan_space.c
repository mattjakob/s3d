#include "raster.h"
#include "prim.h"

void scan_prim(Prim *p, void (*paint)())
{
  Real u, v;
  Inode *l;
  Box3d bb = prim_bbox(p);
  
  for (v = bb.ll.y; v < bb.ur.y; v++) {
    for (u = bb.ll.x; u < bb.ur.x; u++) {
      if (l = prim_intersect(p, ray_make(v3_make(u,v,0), v3_make(0,0,1)))) 
	paint(u,v);
    }
  }
}

