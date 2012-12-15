#include "defs.h"
#include "zsort.h"


List *z_sort(List *p)
{
  List *q = new_list();

  while (!is_empty(p)) {
    Item *i = z_largest(p);
    remove_item(p, i);
    append_item(q, i);
  }
  return q;
}

Item *z_largest(List *p)
{
  Item *i, *s;

  for (s = i = p->head; i != NULL; i=i->next)
    if (((Zdatum *)(i->d))->zmax > ((Zdatum *)(s->d))->zmax)
      s = i;
  return s;
}



