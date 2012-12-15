#include "defs.h"
#include "list.h"


Item *new_item(void *d)
{
  Item *i = NEWSTRUCT(Item);
  i->next = i->prev = NULL;
  i->d = d;
  return i;
}

List *new_list()
{
  List *q = NEWSTRUCT(List);
  q->head = q->tail = NULL;
  return q;
}

int is_empty(List *q)
{
  return (q->head==NULL || q->tail==NULL);
}

void insert_item(List *q, Item *i)
{
  if (is_empty(q)) {
    q->head = q->tail = i;
  } else {
    q->head->prev = i;
    i->next = q->head;
    q->head = i;
  }
}

void append_item(List *q, Item *i)
{
  if (is_empty(q)) {
    q->head = q->tail = i;
  } else {
    i->prev = q->tail;
    q->tail->next = i;
    q->tail = i;
  }
}

void remove_item(List *q, Item *i)
{
  if (is_empty(q)) {
    return;
  } else if (i == q->head) {
    if ((q->head = i->next) != NULL)
      q->head->prev = NULL;
  } else if (i == q->tail) {
    if ((q->tail = i->prev) != NULL)
      q->tail->next = NULL;
  } else {
    Item *prev = i->prev;
    Item *next = i->next;
    i->prev->next = next;
    i->next->prev = prev;
  }
}

void free_list(List *q)
{
  Item *i=q->head;
  while (i!=NULL) {
    Item *t=i;
    i=i->next;
    efree(t);
  }
  efree(q);
}

