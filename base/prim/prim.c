#include "prim.h"


Prim *prim_instance(PrimFuncs *f)
{
  return f->instance(f);
}

void prim_destroy(Prim *p)
{
   (*p->f->destroy)(p);
}

Box3d prim_bbox(Prim *p)
{
  return (*p->f->bbox)(p);
}

int prim_classify(Prim *p, Vector3 q)
{
  return (*p->f->classify)(p, q);
}

Vector3 prim_point(Prim *p, Real u, Real v)
{
  return (*p->f->point)(p, u, v);
}

Vector3 prim_normal(Prim *p, Real u, Real v)
{
  return (*p->f->normal)(p, u, v);
}

Vector3 prim_gradient(Prim *p, Vector3 q)
{
  return (*p->f->gradient)(p, q);
}

Inode *prim_intersect(Prim *p, Ray r)
{
  return (*p->f->intersect)(p, r);
}

Prim *prim_transform(Prim *p, Matrix4 md, Matrix4 mi)
{
  return (*p->f->transform)(p, md, mi);
}

Poly   *prim_uv_decomp(Prim *p, Real level)
{
  return (*p->f->uv_decomp)(p, level);
}

Vector3 prim_texc(Prim *p, Real u, Real v)
{
  return (*p->f->texc)(p, u, v);
}

Vector3 prim_du(Prim *p, Real u, Real v)
{
  return (*p->f->du)(p, u, v);
}

Vector3 prim_dv(Prim *p, Real u, Real v)
{
  return (*p->f->dv)(p, u, v);
}

Matrix4 prim_local(Prim *p)
{
  return (*p->f->local)(p);
}


int prim_id(Prim *p)
{
  return (*p->f->id)(p);
}

void prim_write(Prim *p, FILE *fp)
{
   (*p->f->write)(p, fp);
}

void prim_draw(Prim *p, int axis)
{
   (*p->f->draw)(p, axis);
}

