#include "color.h"

static
Matrix4 rgb_cmy_m =  {{-1.0,  0.0,  0.0, 1.0},
                      { 0.0, -1.0,  0.0, 1.0},
                      { 0.0,  0.0, -1.0, 1.0},
                      { 0.0,  0.0,  0.0, 1.0}
};


Color rgb_to_cmy(Color c)
{
  return v3_m4mult(c, rgb_cmy_m);
}


Color cmy_to_rgb(Color c)
{
  return v3_m4mult(c, rgb_cmy_m);
}


Color rgb_to_yiq(Color c)
{
  Matrix4 rgb_yiq_m ={{0.2989,  0.5866,  0.1144, 0.0},
                      {0.5959, -0.2741, -0.3218, 0.0},
                      {0.2113, -0.5227,  0.3113, 0.0},
                      {0.0,     0.0,     0.0,    1.0}};

  return v3_m4mult(c, rgb_yiq_m);
}


Color yiq_to_rgb(Color c)
{
  Matrix4 yiq_rgb_m ={{1.0,  0.9562,  0.6210, 0.0},
                      {1.0, -0.2717, -0.6485, 0.0},
                      {1.0, -1.1053,  1.7020, 0.0},
                      {0.0,  0.0,     0.0,    1.0}};

  return v3_m4mult(c, yiq_rgb_m);
}


Real rgb_to_y(Color c)
{
  return RED(c)*0.2989 + GRN(c)*0.5866 + BLU(c)*0.1144;
}
