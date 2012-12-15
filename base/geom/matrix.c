#include "geom.h"

Matrix4 m4_zero  = {{0.0, 0.0, 0.0, 0.0},
                    {0.0, 0.0, 0.0, 0.0},
                    {0.0, 0.0, 0.0, 0.0},
                    {0.0, 0.0, 0.0, 0.0}
};

Matrix4 m4_ident()
{
  Matrix4 m = {{1.0, 0.0, 0.0, 0.0},
               {0.0, 1.0, 0.0, 0.0},
               {0.0, 0.0, 1.0, 0.0},
               {0.0, 0.0, 0.0, 1.0}};
  return m;
}

Matrix4 m4_translate(Real tx, Real ty, Real tz)
{
  Matrix4 m = m4_ident();
  m.r1.w = tx;
  m.r2.w = ty;
  m.r3.w = tz;
  return  m;
}

Matrix4 m4_scale(Real sx, Real sy, Real sz)
{
  Matrix4 m = m4_ident();
  m.r1.x= sx;
  m.r2.y= sy;
  m.r3.z= sz;
  return(m);
}

Matrix4 m4_rotate(char axis, Real angle)
{
  Matrix4 m = m4_ident();
  Real cost = (Real) cos(angle);
  Real sint = (Real) sin(angle);
  switch (axis) {
  case 'x' :
    m.r2.y=  cost; m.r2.z= -sint;
    m.r3.y=  sint; m.r3.z=  cost;
    break;
  case 'y' :
    m.r1.x=  cost; m.r1.z=  sint;
    m.r3.x= -sint; m.r3.z=  cost;
    break;
  case 'z' :
    m.r1.x=  cost; m.r1.y= -sint;
    m.r2.x=  sint; m.r2.y=  cost;
    break;
  default :
    error("(m4_rotate) invalid axis\n");
  }
  return  m;
}


 Matrix4 m4_transpose(Matrix4 m)
{
  Matrix4 mt;
  mt.r1.x= m.r1.x;
  mt.r1.y= m.r2.x;
  mt.r1.z= m.r3.x;
  mt.r1.w= m.r4.x;

  mt.r2.x= m.r1.y;
  mt.r2.y= m.r2.y;
  mt.r2.z= m.r3.y;
  mt.r2.w= m.r4.y;

  mt.r3.x= m.r1.z;
  mt.r3.y= m.r2.z;
  mt.r3.z= m.r3.z;
  mt.r3.w= m.r4.z;

  mt.r4.x= m.r1.w;
  mt.r4.y= m.r2.w;
  mt.r4.z= m.r3.w;
  mt.r4.w= m.r4.w;
  return mt ;
}

#if 0
Matrix4 m4_m4prod(Matrix4 a, Matrix4 b)
{
  Matrix4 m, c = m4_transpose(b);

  m.r1.x = v4_dot(a.r1, c.r1);
  m.r1.y = v4_dot(a.r1, c.r2);
  m.r1.z = v4_dot(a.r1, c.r3);
  m.r1.w = v4_dot(a.r1, c.r4);

  m.r2.x = v4_dot(a.r2, c.r1);
  m.r2.y = v4_dot(a.r2, c.r2);
  m.r2.z = v4_dot(a.r2, c.r3);
  m.r2.w = v4_dot(a.r2, c.r4);

  m.r3.x = v4_dot(a.r3, c.r1);
  m.r3.y = v4_dot(a.r3, c.r2);
  m.r3.z = v4_dot(a.r3, c.r3);
  m.r3.w = v4_dot(a.r3, c.r4);

  m.r4.x = v4_dot(a.r4, c.r1);
  m.r4.y = v4_dot(a.r4, c.r2);
  m.r4.z = v4_dot(a.r4, c.r3);
  m.r4.w = v4_dot(a.r4, c.r4);
  return m;
}
#else
Matrix4 m4_m4prod(Matrix4 a, Matrix4 b)
{
  Matrix4 m;
  m.r1.x= a.r1.x*b.r1.x + a.r1.y*b.r2.x + a.r1.z*b.r3.x + a.r1.w*b.r4.x;
  m.r1.y= a.r1.x*b.r1.y + a.r1.y*b.r2.y + a.r1.z*b.r3.y + a.r1.w*b.r4.y;
  m.r1.z= a.r1.x*b.r1.z + a.r1.y*b.r2.z + a.r1.z*b.r3.z + a.r1.w*b.r4.z;
  m.r1.w= a.r1.x*b.r1.w + a.r1.y*b.r2.w + a.r1.z*b.r3.w + a.r1.w*b.r4.w;

  m.r2.x= a.r2.x*b.r1.x + a.r2.y*b.r2.x + a.r2.z*b.r3.x + a.r2.w*b.r4.x;
  m.r2.y= a.r2.x*b.r1.y + a.r2.y*b.r2.y + a.r2.z*b.r3.y + a.r2.w*b.r4.y;
  m.r2.z= a.r2.x*b.r1.z + a.r2.y*b.r2.z + a.r2.z*b.r3.z + a.r2.w*b.r4.z;
  m.r2.w= a.r2.x*b.r1.w + a.r2.y*b.r2.w + a.r2.z*b.r3.w + a.r2.w*b.r4.w;

  m.r3.x= a.r3.x*b.r1.x + a.r3.y*b.r2.x + a.r3.z*b.r3.x + a.r3.w*b.r4.x;
  m.r3.y= a.r3.x*b.r1.y + a.r3.y*b.r2.y + a.r3.z*b.r3.y + a.r3.w*b.r4.y;
  m.r3.z= a.r3.x*b.r1.z + a.r3.y*b.r2.z + a.r3.z*b.r3.z + a.r3.w*b.r4.z;
  m.r3.w= a.r3.x*b.r1.w + a.r3.y*b.r2.w + a.r3.z*b.r3.w + a.r3.w*b.r4.w;

  m.r4.x= a.r4.x*b.r1.x + a.r4.y*b.r2.x + a.r4.z*b.r3.x + a.r4.w*b.r4.x;
  m.r4.y= a.r4.x*b.r1.y + a.r4.y*b.r2.y + a.r4.z*b.r3.y + a.r4.w*b.r4.y;
  m.r4.z= a.r4.x*b.r1.z + a.r4.y*b.r2.z + a.r4.z*b.r3.z + a.r4.w*b.r4.z;
  m.r4.w= a.r4.x*b.r1.w + a.r4.y*b.r2.w + a.r4.z*b.r3.w + a.r4.w*b.r4.w;
  return m;
}
#endif

