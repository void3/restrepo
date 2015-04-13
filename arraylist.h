#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct elem {
  int  number;
  char *member;
} elem_t;

int list_insert(elem_t *, char *);

int list_delete(elem_t *, char *);

void list_show(elem_t *);

#endif
