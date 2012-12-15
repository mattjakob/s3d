#ifndef LIST_H
#define LIST_H


typedef struct Item {
  struct Item *next, *prev;
  int  type;
  void *d;
} Item;

typedef struct List {
  struct Item *head;
  struct Item *tail;
} List;

Item *new_item(void *d);
List *new_list();
int is_empty(List *q);
void insert_item(List *q, Item *i);
void append_item(List *q, Item *i);
void remove_item(List *q, Item *i);
void free_list(List *q);


#endif
