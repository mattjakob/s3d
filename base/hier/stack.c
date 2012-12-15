#include <stdio.h>
#include <math.h>
#include "stack.h"

#define X_AXIS		'x'
#define Y_AXIS		'y'
#define Z_AXIS		'z'


Stack4 *s4_initstack(int size)
{
  int i;
  Matrix4 *m;
  Stack4 *s  = NEWSTRUCT(Stack4);
  
  s->size = size;
  s->mbot = NEWARRAY(size, Matrix4);
  s->ibot = NEWARRAY(size, Matrix4);

  for (m = s->mbot, i = 0; i < s->size; i++)
    *m++ = m4_ident();
  for (m = s->ibot, i = 0; i < s->size; i++)
    *m++ = m4_ident();

  s->mtop = s->mbot;
  s->itop = s->ibot;

  return s;
}

void s4_push(Stack4 *s)
{
  Matrix4 *m;

  if ((s->mtop - s->mbot) >= (s->size - 1))
    error("(s4_push) stack overflow");

  m = s->mtop;
  s->mtop++;
  *s->mtop = *m;

  m = s->itop;
  s->itop++;
  *s->itop = *m;
}

void s4_pop(Stack4 *s)
{
  if (s->mtop <= s->mbot)
    error("(s4_pop) stack underflow");
  s->mtop--;
  s->itop--;
}

void s4_translate(Stack4 *s, Vector3 t)
{
  *s->mtop = m4_m4prod(*s->mtop, m4_translate( t.x, t.y, t.z));
  *s->itop = m4_m4prod(m4_translate(-t.x,-t.y,-t.z), *s->itop);
}

void s4_scale(Stack4 *s, Vector3 v)
{
  *s->mtop = m4_m4prod(*s->mtop, m4_scale(v.x, v.y, v.z));

  if (REL_EQ(v.x, 0.0) || REL_EQ(v.y,0.0) || REL_EQ(v.z,0.0)) 
    error("(s4_scale) unable to invert scale matrix");
  else
    *s->itop = m4_m4prod(m4_scale(1./v.x,1./v.y,1./v.z), *s->itop);
}

void s4_rotate(Stack4 *s, char axis, Real angle)
{
  *s->mtop = m4_m4prod(*s->mtop, m4_rotate(axis,angle));
  *s->itop = m4_m4prod(m4_rotate(axis,-angle), *s->itop);
}

Vector3 s4_v3xform(Stack4 *s, Vector3 v)
{
  return v3_m4mult(v, *s->mtop);
}

Vector3 s4_n3xform(Stack4 *s, Vector3 nv)
{
  return v3_m4mult(nv, m4_transpose(*s->itop));
}

Matrix4 s4_getmat(Stack4 *s)
{
  return *s->mtop;
}

Matrix4 s4_getimat(Stack4 *s)
{
  return *s->itop;
}

static Matrix4 m4_inverse(Matrix4 m)
{
  error("must provide inverse matrix");
  return m4_ident();
}

void s4_loadmat(Stack4 *s, Matrix4 *md, Matrix4 *im)
{
  *s->mtop = *md;
  *s->itop = (im == (Matrix4 *)0)? m4_inverse(*md) : *im;
}

void s4_concmat(Stack4 *s, Matrix4 *md, Matrix4 *im)
{
  *s->mtop = m4_m4prod(*md, *s->mtop );
  if ( im == (Matrix4 *)0)
    *s->itop = m4_m4prod(*s->itop, m4_inverse(*md));
  else
    *s->itop = m4_m4prod(*s->itop, *im);
}

