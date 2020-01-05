#include "codr7/list.h"

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

void c7_list_push_front(struct c7_list *list, struct c7_list *item) {
  c7_list_insert(list->next, item);
}

struct c7_list *c7_list_pop_front(struct c7_list *list) {
  struct c7_list *i = list->next;
  return (i == list) ? NULL : c7_list_remove(i);
}

void c7_list_push_back(struct c7_list *list, struct c7_list *item) {
  c7_list_insert(list, item);
}

struct c7_list *c7_list_pop_back(struct c7_list *list) {
  struct c7_list *i = list->prev;
  return (i == list) ? NULL : c7_list_remove(i);
}
