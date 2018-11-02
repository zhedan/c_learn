#include<stdio.h>
#include<stdlib.h>
#include "single_list.h"


SL* sl_new(){
  SL * new_slist = (SL*)malloc(sizeof(SL));
  new_slist->head = NULL;
  new_slist->tail = NULL;
  new_slist->length = 0;

  return new_slist;
}

SL* sl_from_array(int *arr, int n){
  SL *slist = sl_new();
  for (int i=0; i<n; i++) {
    sl_add(slist, i);
  }

  return slist;
}

int sl_compare(SL *first, SL *second) {
  if (first->length > second->length) {
    return 1;
  }
  else if (first->length < second->length) {
    return -1;
  }
  else {
    SL_NODE *p1, *p2;
    p1 = first->head;
    p2 = second->head;

    for(; p1;){
      if ( p1->value > p2->value) {
        return 1;
      }
      else if (p1->value < p2->value) {
        return -1;
      }
      else {
        p1 = p1->next;
        p2 = p2->next;
      }
    }
  }
}

SL_NODE* sl_head(SL *slist){
  return slist->head;
}

void sl_add(SL *slist, int i){
  SL_NODE *node = (SL_NODE*)malloc(sizeof(SL_NODE));
  node->value = i;
  node->next = NULL;

  if (!slist->head){
    slist->head = node;
  }
  else {
    slist->tail->next = node;
  }
  slist->tail = node;
  slist->length++;
}

void sl_delete(SL *slist, int i) {
    
}


void sl_reverse(SL *slist){
  SL_NODE *p1, *p2, *p3;
  
  p1 = slist->head;
  // zero node
  if (p1 == NULL) {
    return; 
  }  
  p2 = p1->next;

  // single node
  if ( p2 == NULL ) {
    return;
  }

  p3 = p2->next;
  // two nodes
  if (p3 == NULL) {
    p2->next = p1;
  }
  // 3 or 3+ nodes
  else {
    for (;p2;) {
      p2->next = p1;

      p1 = p2;
      p2 = p3;
      // if p1 is last, then p3 already is NULL previouse loop, eg:
      // p1 = last 2th node, 
      //    p2 = last node
      //       p3 = NULL
      if (p3) {
        p3 = p3->next;
      }
    }
  } 
  
  // swap head and tail
  p1 = slist->head;
  slist->head = slist->tail;
  slist->tail = p1;
  slist->tail->next = NULL;
}

void sl_print(SL *slist) {
  SL_NODE *el = NULL;
  SL_FOREACH(el, slist->head, next){
    printf("%d ", el->value);
  }
  printf("\n");
}

