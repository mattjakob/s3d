#include "anim.h"

static Real time = 0;
static Boolean stop = FALSE;


void time_reset(Real t)
{
  time = t;
  stop = FALSE;
}

Boolean time_done(Real tlimit)
{
  return (time > tlimit || stop == TRUE);
}

Real time_incr(Real tincr)
{
  if (!stop)
    time += tincr;
  return time;
}

Real time_get()
{
  return time;
}

Real time_end()
{
  stop = TRUE;
  return time;
}



