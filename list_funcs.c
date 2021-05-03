#include "list_funcs.h"
#include <stdio.h>
#include <stdlib.h>

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
