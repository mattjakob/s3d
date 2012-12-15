#include "raster.h"
#include "prim.h"

static Box3d bound(Vector3 p, Vector3 q);


void subdiv_line(Vector3 p, Vector3 q, void (*paint)())
{
  Box3d bb = bound(p, q);

  if ((bb.ur.x - bb.ll.x) <= 1 && (bb.ur.y - bb.ll.y) <= 1) {
    paint(bb.ll.x, bb.ll.y);
  } else {
    Vector3 m = v3_scale(0.5, v3_add(p,q));
    subdiv_line(p, m, paint);
    subdiv_line(m, q, paint);
  }
}

static Box3d bound(Vector3 p, Vector3 q)
{
  Box3d bb;
  bb.ll.x = MIN(p.x, q.x); bb.ll.y = MIN(p.y, q.y); bb.ll.z = MIN(p.z, q.z);
  bb.ur.x = MAX(p.x, q.x); bb.ur.y = MAX(p.y, q.y); bb.ur.z = MAX(p.z, q.z);
  return bb;
}
