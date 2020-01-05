#ifndef C7_LIST_H
#define C7_LIST_H

#include "codr7/utils.h"

#define _c7_list_do(l, i, _next)			\
  for (struct c7_list *i = (l)->next, *_next = i->next;	\
       i != (l);					\
       i = _next, _next = i->next)

#define c7_list_do(l, i)			\
  _c7_list_do(l, i, c7_unique(next))

struct c7_list {
  struct c7_list *prev, *next;
};

void c7_list_init(struct c7_list *list);
void c7_list_insert(struct c7_list *list, struct c7_list *item);
struct c7_list *c7_list_remove(struct c7_list *list);

void c7_list_push_front(struct c7_list *list, struct c7_list *item);
struct c7_list *c7_list_pop_front(struct c7_list *list);

void c7_list_push_back(struct c7_list *list, struct c7_list *item);
struct c7_list *c7_list_pop_back(struct c7_list *list);

#endif
