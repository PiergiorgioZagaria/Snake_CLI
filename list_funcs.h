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

Ptr_node inserisciInTesta(Ptr_node l, vec num) {
  Ptr_node tmp;
  tmp = malloc(sizeof(node_t));
  if (tmp != NULL) {
    tmp->pos.x = num.x;
    tmp->pos.y = num.y;
    tmp->next = l;
    l = tmp;
  } else
    printf("Mem. esaurita\n");
  return l;
}
#endif
