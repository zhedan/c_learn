#include<stdio.h>
#include "single_list.h"

void test_sl_reverse(){
  printf("test sl_reverse start\n");

  SL *slist = sl_new();

  for(int i=0; i < 10; i++){
    sl_add(slist, i);
  }
  printf("before first sl_reverse:\n");
  sl_print(slist);

  sl_reverse(slist);
  printf("after first sl_reverse:\n");
  sl_print(slist);

  sl_reverse(slist);
  printf("after second sl_reverse:\n");
  sl_print(slist);
}

int main(){
  test_sl_reverse();
}
