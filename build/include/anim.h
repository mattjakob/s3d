#ifndef _ANIM_H
#define _ANIM_H

#include <stdio.h>
#include <math.h>
#include "lang.h"
#include "defs.h"

void time_reset(Real t);
Boolean time_done(Real tlimit);
Real time_incr(Real tincr);
Real time_get();
Real time_end();

Val motor_parse(int pass, Pval *p);

void arg_init(int ac, char **av);
double arg_get_dval(char *s, Real defval);
Val arg_parse(int pass, Pval *p);

#endif
