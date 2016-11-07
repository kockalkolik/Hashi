#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "game.h"
#include "display.h"




  
	
      
int main(void)
{
  
  
  
  char ** board = allocate_2D_char_array();
  
  bool continuer = true;
  while (continuer) {
    clear();
    printf("*****************   HASHIWO TIME !   *****************\n");
    
    printf("Voulez-vous commencer une partie ?\n1 : Oui\n2 : Non\n");
    
    long jouer_reponse = user_input();
    switch (jouer_reponse) {
    case 1:
      break;
    case 2:
      printf("A la prochaine !\n");
      continuer = false;
      continue;
      break;
    default:
      printf("Vous devez répondre par 1 ou 2.\n");
      waiting(2);
      continue;
      break;
    }
    node * node_array;
    int size_node_array;
    printf("Niveau de difficulté :\n1 : Facile\n2 : Moyen\n3 : Difficile\n");
    long level = user_input();
    switch (level) {
    case 1:
      node_array =  get_array('E',&size_node_array);
      break;
    case 2:
      node_array = get_array('M',&size_node_array);
      break;
    case 3:
      node_array = get_array('H',&size_node_array);
      break;
    default:
      printf("Vous devez choisir 1,2 ou 3.\n");
      waiting(2);
      continue;
    }
    
    starting_board(board,BOARD_WIDTH, BOARD_HEIGHT);
    
    
    game jeu = new_game(size_node_array, node_array);
    
    bool game_is_over = false;
    while (!game_is_over) {
      update_board(jeu, node_array, size_node_array, board);
      print_board(board,BOARD_WIDTH, BOARD_HEIGHT);
      
      printf("Que faire ?\n1 Ajouter un pont\n2 : Supprimer un pont\n");
      printf("3 : Verifier ?\n");
      
      dir bridge_direction;
      int correct_input;   
      long node_coord_x;
      long node_coord_y;
      int node_index;
      long nb_bridge;
      long action = user_input();
      switch (action)
	{
	case 1:
	  printf("Coordonnée x du noeud ?\n");
	  node_coord_x = user_input();
	  node_coord_x *= 2;
	  node_coord_x += 2;
	  
	  printf("Coordonnée y du noeud ?\n");	  
	  node_coord_y = user_input();
	  node_coord_y *= 2;
	  node_coord_y += 2;
	  
	  node_index = game_get_node_number(jeu, node_coord_x, node_coord_y);
	  if (node_index == -1) {
	    printf("Ce noeud n'existe pas.\n Veuillez choisir un noeud existant.\n");
	    waiting(2);
	    
	  }
	  else {
	    
	    printf("Direction ?\n1: SOUTH\n2 : NORTH\n3: EAST\n4: WEST\n");    
	    
	    correct_input = get_direction(&bridge_direction);
	    
	    if (correct_input != 0) {
	      printf("Vous devez choisir entre 1 et 4.\n");
	      waiting(2);	      
	    }
	    else {
	      printf("Ajouter 1 ou 2 ponts ?\n");
	      nb_bridge = user_input();
	      switch(nb_bridge) {
	      case 1:
		if (can_add_bridge_dir(jeu, node_index, bridge_direction)) 
		  add_bridge_dir(jeu, node_index, bridge_direction);
		else {
		  printf("Vous ne pouvez pas ajouter un pont dans cette direction.\n");
		  waiting(2);
		}
		break;
	   
	      case 2:
		if (can_add_bridge_dir(jeu, node_index, bridge_direction)) {
		  add_bridge_dir(jeu, node_index, bridge_direction);
		  if (can_add_bridge_dir(jeu, node_index, bridge_direction)) 
		    add_bridge_dir(jeu, node_index, bridge_direction);
		  else {
		    printf("Vous ne pouviez ajouter qu'un pont dans cette direction.\n");
		    waiting(2);
		  }
		}
		else {
		  printf("Vous ne pouvez pas ajouter un pont dans cette direction.\n");
		  waiting(2);
		}
		
		break;
	      default:
		printf("Vous ne pouvez ajouter qu'un ou deux ponts.\n");
		waiting(2);
		break;
	      }
	    }
	    
	  }
	  break;
	case 2:
	  
	  printf("Coordonnée x du noeud ?\n");
	  node_coord_x = user_input();
	  node_coord_x *= 2;
	  node_coord_x += 2;
	  
	  printf("Coordonnée y du noeud ?\n");	  
	  node_coord_y = user_input();
	  node_coord_y *= 2;
	  node_coord_y += 2;
	  node_index = game_get_node_number(jeu, node_coord_x, node_coord_y);
	  if (node_index == -1) {
	    printf("Ce noeud n'existe pas.\n Veuillez choisir un noeud existant.\n");
	    waiting(2);
	  }
	  else {
	    
	    printf("Direction ?\n1: SOUTH\n2 : NORTH\n3: EAST\n4: WEST\n");
	    correct_input = get_direction(&bridge_direction);
	    
	    if (correct_input != 0) {
	      printf("Vous devez choisir entre 1 et 4.\n");
	      waiting(2);
	      
	    }
	    else {
	      printf("Supprimer 1 ou 2 ponts ?\n");
	      nb_bridge = user_input();
	      switch(nb_bridge) {
	      case 1:
		if (get_degree_dir(jeu, node_index, bridge_direction) > 0)
		  {		
		    del_bridge_dir(jeu, node_index, bridge_direction);	
		  }
		else {
		  printf("Il n'y pas de pont à supprimer\n");
		  waiting(2);
		
		}
	      
		break;
		
	      case 2:
		if (get_degree_dir(jeu, node_index, bridge_direction) > 0)
		  {		
		    del_bridge_dir(jeu, node_index, bridge_direction);	
		    if (get_degree_dir(jeu, node_index, bridge_direction) > 0)
		      {		
			del_bridge_dir(jeu, node_index, bridge_direction);	
		      }
		    else {
		      printf("Il n'y avait qu'un pont à supprimer\n");
		      waiting(2);
		
		    }
		  }
		else {
		  printf("Il n'y pas de pont à supprimer\n");
		  waiting(2);
		
		}
		  
		break;
	      default:
		printf("Vous ne pouvez supprimer qu'un ou deux ponts.\n");
		waiting(2);
		break;
	      }
	    }
	  }
	  break;
	  

	case 3:
	  ;
	  bool verif = game_over(jeu);
	      
	  if (verif) {
	       
	    game_is_over = true;
	    printf("Felicitation ! Vous avez gagné !!!!\n\n\n");
	    waiting(2);
	    
	  }
	  else {
	      
	    printf("Perdu ! Try again !\n\n\n");
	    game_is_over = true;
	    waiting(2);
	  }
		 
	  break;
	default:
	  printf("Vous devez choisir entre 1,2 et 3.\n");
	  waiting(2);
	  break;
	  
	  
	  
      
	  
	}
            
    }
    
    for (int i = 0 ; i < size_node_array; i++)
      delete_node(node_array[i]);
    
    delete_game(jeu);
  }
  free_board(board);
  return EXIT_SUCCESS;
}
