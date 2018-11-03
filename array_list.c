#include<stdlib.h>
#include<stdio.h>
#include "array_list.h"

ArrayList alist_new(int capacity){
  ArrayList alist;
  if (capacity < 0) {
    capacity = 0;
  }
  alist.data = (int *)malloc(sizeof(int) * capacity);
  alist.length = 0;

  alist.capacity = capacity;
  alist.step = 1;

  return alist;
}

int alist_get(ArrayList alist, int index) {
  int length = alist.length;
  int step = alist.step;
  if (step < 0) {
    if (index == 0 ){
      index = length - 1;
    }
    else {
      length -= 1; 
      index = length + step * index;
    }
  }
  return alist.data[index];
}

static ArrayList _alist_add(ArrayList alist, int elem){
  alist.data[alist.length++] = elem;
  return alist;
}

static ArrayList alist_expand(ArrayList src) {
    ArrayList new_alist = alist_new(src.capacity * 2);
    for (int i = 0; i < src.length; i++) {
      new_alist = _alist_add(new_alist, alist_get(src, i));
    }

    free(src.data);
    src.data = NULL;
    return new_alist; 
}

ArrayList alist_add(ArrayList alist, int elem){
  if (alist.step > 0){
    if (alist.length < alist.capacity){
      alist = _alist_add(alist, elem);
      return alist; 
    }
    else {
      ArrayList new_alist = alist_expand(alist);
      return _alist_add(new_alist, elem);
    }
  }
  else {
    ArrayList new_alist = alist_expand(alist);
    return _alist_add(new_alist, elem);
  }
}

ArrayList alist_reverse(ArrayList alist) {
  alist.step = -1; 
  return alist;
}

void alist_print(ArrayList alist) {
  for (int i = 0; i< alist.length; i++) {
    printf("%d ", alist_get(alist, i));
  }
  printf("\n");
}
