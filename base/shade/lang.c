#include <stdio.h>
#include <math.h>
#include "shade.h"


Val distlight_parse(int pass, Pval *pl)
{
  Val v = {V_NULL, 0};;
  if (pass == T_EXEC) {
    Light *l = NEWSTRUCT(Light);
    l->type = LIGHT_DISTANT;
    l->color = C_WHITE;
    l->ambient = pvl_get_num(pl, "ambient", .1);
    l->intensity = pvl_get_num(pl, "intensity", .9);
    l->dir = v3_unit(pvl_get_v3(pl, "direction", v3_make(1,1,1)));
    l->transport = distantlight;
    l->tinfo = NULL;
    v.type = V_LIGHT;
    v.u.v = l;
  }
  return v;
}


Val plastic_parse(int pass, Pval *pl)
{
  Val v = {V_NULL, 0};
  if (pass == T_EXEC) {
    Material *m = NEWSTRUCT(Material);
    m->c = pvl_get_v3(pl, "d_col", C_WHITE);
    m->s = pvl_get_v3(pl, "s_col", C_BLACK);
    m->ka = pvl_get_num(pl, "ka", .1);
    m->kd = pvl_get_num(pl, "kd", .9);
    m->ks = pvl_get_num(pl, "ks", 0);
    m->kt = pvl_get_num(pl, "kt", 0);
    m->se = pvl_get_num(pl, "se", 10);
    m->ir = pvl_get_num(pl, "ir", 1);
    m->luminance = plastic;
    m->tinfo = NULL;
    v.type = V_MATERIAL;
    v.u.v = m;
  }
  return v;
}
