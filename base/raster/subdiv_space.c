#include "raster.h"
#include "prim.h"

static int same_side(Vector3 p, Vector3 q, Box3d bb);
static int disjoint(Vector3 p, Vector3 q, Box3d bb);
static Box3d b_split(Box3d b, int quadrant);


void subdiv_boxline(Box3d bb, Vector3 p, Vector3 q, void (*paint)())
{

  if (disjoint(p, q, bb))
    return;

  if ((bb.ur.x - bb.ll.x) <= 1 && (bb.ur.y - bb.ll.y) <= 1) {
    paint(bb.ll.x, bb.ll.y);
  } else {
    subdiv_boxline(b_split(bb, 1), p, q, paint);
    subdiv_boxline(b_split(bb, 2), p, q, paint);
    subdiv_boxline(b_split(bb, 3), p, q, paint);
    subdiv_boxline(b_split(bb, 4), p, q, paint);
  }
}


static int same_side(Vector3 p, Vector3 q, Box3d bb)
{
  Vector3 l = v3_cross(v3_make(p.x,p.y,1),v3_make(q.x,q.y,1));
  Real d0 = v3_dot(l,v3_make(bb.ll.x, bb.ll.y, 1));
  Real d1 = v3_dot(l,v3_make(bb.ll.x, bb.ur.y, 1));
  Real d2 = v3_dot(l,v3_make(bb.ur.x, bb.ur.y, 1));
  Real d3 = v3_dot(l,v3_make(bb.ur.x, bb.ll.y, 1));

  return ((d0 < 0 && d1 < 0 && d2 < 0 && d3 < 0)
           || (d0 > 0 && d1 > 0 && d2 > 0 && d3 > 0));

}

static int disjoint(Vector3 p, Vector3 q, Box3d bb)
{
  if (((p.x < bb.ll.x) && (q.x < bb.ll.x)) || ((p.y < bb.ll.y) && (q.y < bb.ll.y)))
    return TRUE;
  if (((p.x > bb.ur.x) && (q.x > bb.ur.x)) || ((p.y > bb.ur.y) && (q.y > bb.ur.y)))
    return TRUE;
  return same_side(p, q, bb);
}


static Box3d b_split(Box3d b, int quadrant)
{
  switch (quadrant) {
  case 1: b.ll= v3_scale(0.5, v3_add(b.ll,b.ur)); break;
  case 2: b.ll.x = (b.ll.x + b.ur.x) * 0.5; b.ur.y = (b.ll.y + b.ur.y) * 0.5; break;
  case 3: b.ur= v3_scale(0.5, v3_add(b.ll,b.ur)); break;
  case 4: b.ll.y = (b.ll.y + b.ur.y) * 0.5; b.ur.x = (b.ll.x + b.ur.x) * 0.5; break;
  }
  return b;
}




