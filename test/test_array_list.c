#include<stdio.h>
#include "array_list.h"

int main(){
  ArrayList alist = alist_new(1);
  for (int i = 0; i < 10; i++) {
    alist = alist_add(alist, i);
  }
  printf("before reverse: ");
  alist_print(alist);
  alist = alist_reverse(alist);
  printf("after reverse: ");
  alist_print(alist);

  printf("after reverse, then add element: ");
  alist = alist_add(alist, 50);
  alist_print(alist);
}
