#ifndef CLIP_H
#define CLIP_H

int is_backfacing(Poly *p, Vector3 v);
int cull_poly(Real h, Poly *p);

int poly_clip(Real h, Poly *p, void (*dispose)(), int chain);

int hither_clip(Real h, Poly *p, void (*render)(), void (*plfree)());
int hclip(Real h, Poly *p, void (*render)(), void (*plfree)());


#endif
