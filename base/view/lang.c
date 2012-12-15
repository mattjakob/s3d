#include "defs.h"
#include "geom.h"
#include "view.h"
#include "lang.h"
#include "sdltypes.h"

Val view_parse(int pass, Pval *pl)
{
  Val v = {V_NULL, 0};
  if (pass == T_EXEC) {
    View *view = initview();

    Vector3 ref = pvl_get_v3(pl, "from", v3_make(0,-5,0));
    Vector3 at = pvl_get_v3(pl, "at", v3_make(0,0,0));
    Vector3 up = pvl_get_v3(pl, "up", v3_make(0,0,1));
    double fov = pvl_get_num(pl, "fov", 90);
    double w = pvl_get_num(pl, "imgw", 320);
    double h = pvl_get_num(pl, "imgh", 240);

    lookat(view, ref.x, ref.y, ref.z, at.x, at.y, at.z, up.x, up.y, up.z);
    setviewpoint(ref.x, ref.y, ref.z);
    setviewnormal(at.x - ref.x ,at.y - ref.y, at.z - ref.z);
    makeviewV();

    perspective(view, fov * DTOR, w/h, 1.0, 100000.0);
    viewport(view, 0.,0., w, h);

    v.type = V_CAMERA;
    v.u.v = view;
  }
  return v;
}
