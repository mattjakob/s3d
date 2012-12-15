#include <stdio.h>
#include <math.h>
#include "map.h"
#include "sdltypes.h"


TextureSrc *default_tsrc()
{
  TextureSrc *s = NEWSTRUCT(TextureSrc);
  s->texfunc = texture_default;
  return s;
}

TextureSrc *parse_texsource(Pval *pl)
{
  Pval *p = pl;
  while (p != NULL) {
    if (p->name && strcmp(p->name,"tex_src") == 0) {
      if (p->val.type == V_TEX_IMG || p->val.type == V_TEX_FUNC)
	return (TextureSrc *)(p->val.u.v);
    }
    p = p->next;
  }
  return default_tsrc();
}

int parse_code(Pval *pl)
{
  Pval *p = pl;
  while (p != NULL) {
    if (p->name && strcmp(p->name,"code") == 0 && p->val.type) {
      if (strcmp(p->val.u.v, "tile") == 0)
	return TMAP_TILE;
      else if (strcmp(p->val.u.v, "clamp") == 0)
	return TMAP_CLAMP;
    }
    p = p->next;
  }
  return TMAP_CLAMP;
}


Val textured_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) {
    Material *m = NEWSTRUCT(Material);
    TmapInfo *ti = NEWSTRUCT(TmapInfo);
    
    m->c = pvl_get_v3(pl, "d_col", C_WHITE);
    m->s = pvl_get_v3(pl, "s_col", C_WHITE);
    m->ka = pvl_get_num(pl, "ka", .1);
    m->kd = pvl_get_num(pl, "kd", .6);
    m->ks = pvl_get_num(pl, "ks", .3);
    m->se = pvl_get_num(pl, "se", 10);
    m->luminance = textured_plastic;

    ti->src = parse_texsource(pl);
    ti->bg = pvl_get_v3(pl, "bg_col", C_WHITE);
    ti->code = parse_code(pl);
    m->tinfo = ti;
    v.type = V_MATERIAL;
    v.u.v = m;
  }
  return v;
}

Val imagemap_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) { 
    Pval *p = pl;
    TextureSrc *i = NEWSTRUCT(TextureSrc);
    i->texfunc = texture_default;
    while (p != NULL) {
      if (p->name && strcmp(p->name,"fname") == 0 && p->val.type == V_STR) {
	i->texfunc = image_texture;
	i->texdata = img_read(p->val.u.v);
      }
      p = p->next;
    }
    v.type = V_TEX_IMG;
    v.u.v = i;
  }
  return v;
}



Val rough_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) {
    Material *m = NEWSTRUCT(Material);
    
    m->c = pvl_get_v3(pl, "d_col", C_WHITE);
    m->ka = pvl_get_num(pl, "ka", .1);
    m->kd = pvl_get_num(pl, "kd", .6);
    m->luminance = rough_surface;
    m->tinfo = parse_texsource(pl);
    v.type = V_MATERIAL;
    v.u.v = m;
  }
  return v;
}

Val shiny_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) {
    Material *m = NEWSTRUCT(Material);
    
    m->c = pvl_get_v3(pl, "d_col", C_WHITE);
    m->ka = pvl_get_num(pl, "ka", .3);
    m->ks = pvl_get_num(pl, "ks", .8);
    m->se = pvl_get_num(pl, "se", 10);
    m->luminance = shiny_surface;
    m->tinfo = parse_texsource(pl);
    v.type = V_MATERIAL;
    v.u.v = m;
  }
  return v;
}


Val slideproj_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) {
    Light *l = NEWSTRUCT(Light);
    TslideInfo *ti = NEWSTRUCT(TslideInfo);
    l->type = LIGHT_DISTANT;
    l->color = C_WHITE;
    l->ambient = 0.1;
    l->intensity = pvl_get_num(pl, "intensity", 1);
    l->cutoff = (DTOR * pvl_get_num(pl, "fov", 90))/2.0;
    l->distr = 1/tan(l->cutoff);
    l->loc = pvl_get_v3(pl, "from", v3_make(0,0,-1));
    l->dir = pvl_get_v3(pl, "at", v3_make(0,0,0));
    l->dir = v3_unit(v3_sub(l->dir, l->loc));
    l->transport = slide_projector;

    ti->src = parse_texsource(pl);
    ti->v = v3_unit(v3_cross(l->dir, v3_cross(l->dir, v3_make(0,1,0))));
    ti->u = v3_cross(l->dir, ti->v);
    l->tinfo = ti;

    v.type = V_LIGHT;
    v.u.v = l;
  }
  return v;
}


Val chequer_parse(int pass, Pval *pl)
{
  Val v = {0, 0};
  if (pass == T_EXEC) { 
    TextureSrc *i = NEWSTRUCT(TextureSrc);
    ChequerInfo *c = NEWSTRUCT(ChequerInfo);
    c->xfreq = pvl_get_num(pl, "x_freq", 1);
    c->yfreq = pvl_get_num(pl, "y_freq", 1);
    c->fg = pvl_get_v3(pl, "fg_col", C_BLACK);
    c->bg = pvl_get_v3(pl, "bg_col", C_WHITE);
    i->texfunc = chequer_texture;
    i->texdata = c;
    v.type = V_TEX_FUNC;
    v.u.v = i;
  }
  return v;
}

