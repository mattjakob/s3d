#include "ray.h"

int n_inode = 0;

Inode *inode_alloc(Real t, Vector3 n, int enter)
{
  Inode *i = NEWSTRUCT(Inode);
  i->t = t;
  i->n = n;
  i->enter = enter;
  i->next = (Inode *)0;
  return i;
}

void inode_free(Inode *l)
{
  Inode *i;
  while (l) {
    i = l; l = l->next; free(i);
  }
}

