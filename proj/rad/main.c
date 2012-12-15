#include "main.h"

#define RD_EPS   2
#define MAX_ITER 100
//#define VISIB    FALSE
#define VISIB    TRUE
#define ELEM_SIZ 80

static Scene *s;
static RadData *rd;
static Matrix4 mclip, mdpy;


int main(int argc, char **argv)
{
  Poly *p; Color c, *cols; int k;

  init_sdl();
  s = scene_read();
  init_render();

  radiosity_set(RD_EPS, MAX_ITER, VISIB);
  cols = radiosity_prog(rd->n, rd->pl, rd->e, rd->rho);

  for (k = 0; k < rd->n; k++) {
    p = rd->pl[k];
    if (is_backfacing(p, v3_sub(poly_centr(p), s->view->center)))
      continue;
    c = cols[k];
    if (poly_clip(VIEW_ZMIN(s->view), poly_transform(p, mclip), 0, 0))
      scan_poly(poly_homoxform(p, mdpy), pix_paint, &c);
  }
  img_write(s->img, "stdout", 0);
  exit(0);
}


void pix_paint(Vector3 v,int n,int lv,Real lt,int rv,Real rt,Real st, void *c)
{
  if (zbuf_store(v))
    img_putc(s->img, v.x, v.y, col_dpymap(*((Color *)(c))));
}

void init_render(void)
{
  mclip = m4_m4prod(s->view->C, s->view->V);
  mdpy = m4_m4prod(s->view->S, s->view->P);

  zbuf_init(s->img->w, s->img->h);
  rd = make_rad_data(s->objs);
} 

void init_sdl(void)
{
  lang_defun("scene", scene_parse);
  lang_defun("view", view_parse);
  lang_defun("dist_light", distlight_parse);
  lang_defun("plastic", plastic_parse);
  lang_defun("polyobj", obj_parse);
  lang_defun("trilist", trilist_parse);
}

RadData *make_rad_data(Object *ol)
{
  Object *o; Poly *p; int k;
  RadData *rd = NEWSTRUCT(RadData);

  for (rd->n = 0, o = ol; o != NULL; o = o->next) {
    if (o->type == V_POLYLIST) {
      o->u.pols = plist_refine(p = o->u.pols, ELEM_SIZ, 4);
      rd->n += (k = plist_lenght(o->u.pols));
      free(p);
    }
  }
  rd->pl = NEWARRAY(rd->n, Poly *);
  rd->e = NEWARRAY(rd->n, Vector3);
  rd->rho = NEWARRAY(rd->n, Vector3);

  for (k = 0, o = ol; o != NULL; o = o->next) {
    if (o->type != V_POLYLIST)
      continue;
    for (p = o->u.pols; p != NULL; p = p->next) {
      rd->pl[k] = p;
      rd->rho[k] = c_scale(o->mat->kd, o->mat->c);
      rd->e[k] = c_scale(o->mat->ks, o->mat->s);
      k++;
    }
  }
  return rd;      
}
