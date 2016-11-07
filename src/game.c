#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/game.h"

#define NB_DIRS 4


game new_game (int nb_nodes, node *nodes){
   game jeu = malloc (sizeof(game));
   if (jeu == NULL) {
        fprintf(stderr, "not enough memory!\n");
        exit (EXIT_FAILURE);
	}
   jeu->nb_nodes=nb_nodes;
   jeu->nodes=nodes;
   return jeu;
}


void delete_game (game g) {
    for (int k = 0; k < g->nb_nodes; k++) {
        delete_node(g->nodes[k]);
    }
    free(g);
}

game copy_game (cgame g_src) {
   node *nodes=g_src->nodes;
   int nb_nodes=g_src->nb_nodes;
   game cjeu=new_game(nb_nodes, nodes);
   return cjeu;
}


int game_nb_nodes (cgame g) {
	return g->nb_nodes;
}

node game_node (cgame g, int node_num){
   if (node_num >= 0 && node_num <= game_nb_nodes(g)){
      for (int k = 0; k < g->nb_nodes; k++) {
         if (g->nodes[k]->degree==node_num){
            return g->nodes[k];
         }
      }
   }
}
