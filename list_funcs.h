#ifndef LIST_FUNC_H_INCLUDED
#define LIST_FUNC_H_INCLUDED
typedef struct {
  int x;
  int y;
} vec;

typedef struct node {
  vec pos;
  struct node *next;
} node_t;

typedef node_t *Ptr_node;

Ptr_node inserisciInTesta(Ptr_node l, vec num);
#endif
