#ifndef SL_NODE_H
#define SL_NODE_H 

struct SL_NODE{
  int value;
  struct SL_NODE *next;
};

typedef struct SL_NODE SL_NODE;

typedef struct SL{
  SL_NODE *head;
  SL_NODE *tail;
  int length;
} SL;

SL* sl_new();
SL* sl_from_array();
int sl_compare(SL *first, SL *second);
void sl_add(SL *slist, int i);
void sl_delete(SL *slist, int i);
void sl_delete_one(SL *slist, int i);
void sl_reverse(SL *slist);
void sl_print(SL *slist);

#define SL_FOREACH(var, head, field) \
  for ((var)=(head); (var); (var)=(var)->field)

#endif
