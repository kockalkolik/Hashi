#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "game.h"
#include "display.h"


#define NB_EASY_LVL 1
#define NB_MEDIUM_LVL 1
#define NB_HARD_LVL 1

char ** allocate_2D_char_array() {
  char ** board = (char **) malloc (BOARD_WIDTH * sizeof(char *));
  if (board == NULL) {
    fprintf(stderr, "Not enough memory !\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < BOARD_WIDTH; i++) {
    board[i] = (char *) malloc (BOARD_HEIGHT * sizeof(char));
    if (board[i] == NULL) {
      fprintf(stderr, "Not enough memory !\n");
      exit(EXIT_FAILURE);
    }
  }
  return board;
}

void starting_board(char ** board, int width, int height) {
  char tmpx = 48;
  char tmpy = 57;
  for (int j = height-1; j >= 0; j--) {
    
    for (int i = 0; i < width; i++) {
      
      if (i > 0 && j == 0 && (i % 2 == 0)) {
	board[j][i] = tmpx;
	tmpx++;
      }
      else if (i >= 1 && j == height - 1) {
	board[j][i] = '-';
      }
      else if (i >= 1 && j == 1) {
	board[j][i] = '-';
      }
      else if (i == 0 && j < height - 1 && j > 0 && j % 2 == 0) {
	board[j][i] = tmpy;
	tmpy--;
      }
      else if (i == 1 && j < height - 1 && j > 1) {
	board[j][i] = '|';
      }
      else if (i == 21 && j < height - 1 && j > 1) {
	board[j][i] = '|';
      }
      else {
	board[j][i] = ' ';
      }
    }
    printf("\n");
  }
}
void print_board(char ** board, int width, int height) {
  clear();
  for (int j = height-1; j >= 0; j--) {
    for (int i = 0; i < width; i++) {
      printf("%c", board[j][i]);
    }
    printf("\n");
  }
  printf("\n");
}
void update_board(game jeu, node *nodes, int size_node_array, char ** board) {
  
  
  for (int i = 0; i < size_node_array; i++) {
    int x = get_x(nodes[i]);
    int y = get_y(nodes[i]);
    int degree = get_required_degree(nodes[i]);
    // +48 to match the ascii table
    board[y][x] = degree+48;
    int bridges_EAST = get_degree_dir(jeu,i,EAST);
    int bridges_SOUTH = get_degree_dir(jeu,i,SOUTH);

    if (bridges_EAST == 0) {
      int neighbour = get_neighbour_dir(jeu,i,EAST);
      if (neighbour != -1) {
	int neighbour_x = get_x(nodes[neighbour]);
	for (int k = x+1; k < neighbour_x; k++) {
	  if (board[y-1][k] == '|'  || board[y+1][k] == '|' ) {
	    board[y][k] = '|';
	  }
	  else if (board[y-1][k] == 'H'  || board[y+1][k] == 'H') {
	    board[y][k] = 'H';
	  }
	  else {
	    board[y][k] = ' ';
	  }
	       
	}
      }
    }
    if (bridges_EAST == 1) {
      int neighbour = get_neighbour_dir(jeu,i,EAST);
      if (neighbour != -1) {
	int neighbour_x = get_x(nodes[neighbour]);
	for (int k = x+1; k < neighbour_x; k++) {
	  board[y][k] = '_';
	}
      }
    }
    if (bridges_EAST == 2) {
      int neighbour = get_neighbour_dir(jeu,i,EAST);
      if (neighbour != -1) {
	int neighbour_x = get_x(nodes[neighbour]);
	for (int k = x+1; k < neighbour_x; k++) {
	  board[y][k] = '=';
	}
      }
    }
    if (bridges_SOUTH == 0) {
      int neighbour = get_neighbour_dir(jeu,i,SOUTH);
      if (neighbour != -1) {
	int neighbour_y = get_y(nodes[neighbour]);
	for (int k = y-1; k > neighbour_y; k--) {
	  board[k][x] = ' ';
	}
      }
    }
    if (bridges_SOUTH == 1) {
      int neighbour = get_neighbour_dir(jeu,i,SOUTH);
      if (neighbour != -1) {
	int neighbour_y = get_y(nodes[neighbour]);
	for (int k = y-1; k > neighbour_y; k--) {
	  board[k][x] = '|';
	}
      }
    }
    if (bridges_SOUTH == 2) {
      int neighbour = get_neighbour_dir(jeu,i,SOUTH);
      if (neighbour != -1) {
	int neighbour_y = get_y(nodes[neighbour]);
	for (int k = y-1; k > neighbour_y; k--) {
	  board[k][x] = 'H';
	}
      }
    }
    
  }

}

void flushing(char *x) {
  char Junk[16];
  if( x[strlen(x)-1] != '\n' ) {
    do fgets(Junk,16,stdin);
    while( Junk[strlen(Junk)-1] != '\n' ); }
  else x[strlen(x)-1] = '\0';
}

long user_input() {
  char input[10];
  char *ptr;
  long ret;
  fgets(input, 10, stdin);
  ret = strtol(input, &ptr, 10);
  flushing(input);
  return ret;
}

    
int get_direction(dir * pdirection_input) {
  long bridge_direction = user_input();
  
  switch (bridge_direction) {
  case 1:
    *pdirection_input = SOUTH;
    return 0;
   
  case 2:
    *pdirection_input = NORTH;
    return 0;
    
  case 3:
    *pdirection_input = EAST;
    return 0;
    
  case 4:
    *pdirection_input = WEST;
    return 0;
    
  default:
    return -1;	      
    
  }
}


int * read_file_array(char lvl, char nb, int * ptaille) {
  FILE * pFile = fopen("array.txt", "r");
  char input[50];
  int * array;
  int taille;
  while (fgets(input, 50, pFile)) {
    if (input[0] == lvl && input[1] == nb) {
      fgets(input, 50, pFile);
      char  char_taille[3];
      if (input[1] != '\n') {
	char_taille[0] = input[0];
	char_taille[1] = input[1];
      }
      else {
	char_taille[0] = '0';
	char_taille[1] = input[0];
      }
      taille = atoi(char_taille);
            
      *ptaille = taille;
      array = (int *) malloc ((taille*3) * sizeof(int));
      if (array == NULL) {
	fprintf(stderr, "Not enough memory !\n");
	exit(EXIT_FAILURE);
      }
      for (int i = 0; i < taille*3; i +=3) {
	fgets(input,50, pFile);
	char x[2];
	x[0] = input[0];
       	array[i] = atoi(x)*2 + 2;
	

	char y[2];
	y[0] = input[2];
	array[i+1] = atoi(y)*2 + 2;
	int tmp = input[4] - 48;
	if (tmp > 0 && tmp < 9) {
	  array[i+2] = tmp;
	}
	else {
	  fprintf(stderr, "A node must have between 1 and 8 bridges.\n");
	  exit(EXIT_FAILURE);
	}
	
      }

    }
  }
  
  return array;
}


node * int_to_node_array(int * int_array, int * ptaille) {
  node * node_array = (node *) malloc ((*ptaille) * sizeof(node));
  if (node_array == NULL) {
    fprintf(stderr, "Not enough memory !\n");
    exit(EXIT_FAILURE);
  }
  int j = 0;
  for (int i = 0; i < *ptaille; i++) {
    node_array[i] = new_node(int_array[j], int_array[j+1], int_array[j+2]);
    j +=3;
  }
  free(int_array);
  return node_array;
}


node * get_array(char lvl, int * ptaille) {
  srand(time(NULL));
  int nb;
  int * int_array;
  if (lvl == 'E') {
    int tmp = NB_EASY_LVL;
    if (tmp <= 0) {
      fprintf(stderr, "No easy array available\n");
      exit(EXIT_FAILURE);
    }
    nb = (rand()%tmp) + 1;
    char nb_str[2];
    snprintf(nb_str, 2, "%d", nb);
    int_array = read_file_array(lvl, nb_str[0], ptaille);
    
    
  }
  else if (lvl == 'M') {
    int tmp = NB_MEDIUM_LVL;
    if (tmp <= 0) {
      fprintf(stderr, "No medium array available\n");
      exit(EXIT_FAILURE);
    }
    nb = (rand()%tmp) + 1;
    char nb_str[2];
    snprintf(nb_str, 2, "%d", nb);
    int_array = read_file_array('M', nb_str[0], ptaille);
    
  }
  else {
    int tmp = NB_HARD_LVL;
    if (tmp <= 0) {
      fprintf(stderr, "No hard array available\n");
      exit(EXIT_FAILURE);
    }
    nb = (rand()%tmp) + 1;
    char nb_str[2];
    snprintf(nb_str, 2, "%d", nb);
    int_array = read_file_array('H', nb_str[0], ptaille);
    
  }
  return int_to_node_array(int_array, ptaille);
}


void clear() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}

void waiting(int seconds) {
  time_t actual_time = time(NULL);

  while (time(NULL) != actual_time + seconds) {
  }
}


void free_board(char ** board) {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    free(board[i]);
  }
  free(board);
}
