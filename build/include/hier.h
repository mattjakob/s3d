#ifndef HIER_H
#define HIER_H

#include "lang.h"

Val group_parse(int pass, Pval *pl);
Val translate_parse(int pass, Pval *p);
Val scale_parse(int pass, Pval *p);
Val rotate_parse(int pass, Pval *p);

#endif
