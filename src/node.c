#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node new_node (int abs, int ordo, int required_degree){
  node noeud = malloc (sizeof(node_s));
  if (noeud == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    exit(EXIT_FAILURE);
  }
  noeud -> x = abs;
  noeud -> y = ordo;
  noeud -> degree = required_degree;
  
  return noeud;
}

void delete_node (node n){
  free(n);
}
 
int get_x (node n){
  return n -> x;
}

int get_y (node n){
  return n -> y;
}

int get_required_degree (node n){
  return n -> degree;
}

