#ifndef _DISPLAY_H_
#define _DISPLAY_H
#include <string.h>
#include "node.h"
#include "game.h"

#define BOARD_WIDTH 22
#define BOARD_HEIGHT 22

char ** allocate_2D_char_array();
void starting_board(char ** board, int width, int height);
void print_board(char ** board, int width, int height);
void update_board(game jeu, node *nodes, int size_node_array, char ** board);
int get_direction(dir * pdirection_input);
node * get_array(char lvl, int * ptaille);
int * read_file_array(char lvl, char nb, int * ptaille);
node * int_to_node_array(int * int_array, int * ptaille);
void flushing(char *x);
long user_input();
void clear();
void waiting(int seconds);
void free_board(char ** board);
#endif
