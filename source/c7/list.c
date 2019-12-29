#include "c7/list.h"

void c7_list_init(struct c7_list *list) {
  list->prev = list->next = list;
}

void c7_list_insert(struct c7_list *list, struct c7_list *item) {
  item->prev = list->prev;
  list->prev->next = item;
  item->next = list;
  list->prev = item;
}

struct c7_list *c7_list_remove(struct c7_list *list) {
  list->prev->next = list->next;
  list->next->prev = list->prev;
  return list;
}
