#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
typedef struct ArrayList {
  int length;
  int capacity;
  int *data;
  int step;
} ArrayList;

ArrayList alist_new(int capacity);
ArrayList alist_add(ArrayList alist, int elem);
ArrayList alist_reverse(ArrayList alist);
int alist_get(ArrayList alist, int index);
void alist_print(ArrayList alist);

#endif
