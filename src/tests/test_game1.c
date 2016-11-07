#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "test_toolbox.h"



/* Defalult configuration
   2     2     3

   5     1

   3           2
*/

#define EXAMPLE_NB_NODE 7
int vals[EXAMPLE_NB_NODE][3] = {{0,0,3},{0,1,5},{0,2,2},{1,1,1},{1,2,2},{2,0,2},{2,2,3}};

static game default_game () {
    node nodes[EXAMPLE_NB_NODE];
    for (int i = 0 ; i < EXAMPLE_NB_NODE; i++)
      nodes[i] = new_node(vals[i][0],vals[i][1],vals[i][2]);
    game g = new_game(EXAMPLE_NB_NODE, nodes);
    for (int i = 0 ; i < EXAMPLE_NB_NODE; i++)
      delete_node(nodes[i]);
    return g;
}


bool test_get_node_number() {
    game g = default_game();
    bool r = true;

    for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
      int num = game_get_node_number (g, vals[i][0], vals[i][1]);
      r = r && test_interval_int(0,EXAMPLE_NB_NODE-1, num, "Pb game_node_number");
      node n = game_node(g, num);
      r = r && test_equality_int(vals[i][2], get_required_degree(n), "Pb with degrees");
    }
    r = r && test_equality_int(-1, game_get_node_number (g, 1, 0), "Pb game_node_number");
    r = r && test_equality_int(-1, game_get_node_number (g, 2, 1), "Pb game_node_number");
    delete_game(g);
    return r;
}

bool test_can_add_bridge_dir() {
  game g = default_game();
  bool r = true;
  int num = game_get_node_number (g, 0, 0);
  r = r && test_equality_bool(true, can_add_bridge_dir(g, num, NORTH), "can add NORTH");
  r = r && test_equality_bool(true, can_add_bridge_dir(g, num, EAST), "can add EAST");
  r = r && test_equality_bool(false, can_add_bridge_dir(g, num, WEST), "can add WEST");
  r = r && test_equality_bool(false, can_add_bridge_dir(g, num, SOUTH), "can add SOUTH");
  delete_game(g);
  return r;
}



bool test_get_neighbour() {
  game g = default_game();
  bool r = true;
  r = r && test_equality_int(5, get_neighbour_dir(g,0,EAST), "pb neighbour 0 EAST");
  r = r && test_equality_int(4, get_neighbour_dir(g,2,EAST), "pb neighbour 2 EAST");
  r = r && test_equality_int(0, get_neighbour_dir(g,1,SOUTH), "pb neighbour 1 SOUTH");
  r = r && test_equality_int(2, get_neighbour_dir(g,1,NORTH), "pb neighbour 1 NORTH");

  delete_game(g);
  return r;
}

bool test_get_degree () {
  game g = default_game();
  bool r = true;
  for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
    r = r && test_equality_int(0, get_degree(g, i), "pb number of bridges connected");
  }
  
  add_bridge_dir(g, 0, EAST);
  r = r && test_equality_int(1, get_degree(g, 0), "pb number of bridges connected");
  add_bridge_dir(g, 0, EAST);
  r = r && test_equality_int(2, get_degree(g, 0), "pb number of bridges connected");
  del_bridge_dir(g, 0, EAST);
  del_bridge_dir(g, 0, EAST);
  r = r && test_equality_int(0, get_degree(g, 0), "pb number of bridges connected");
  delete_game(g);
  return r;
}

bool test_get_degree_dir () {
  game g = default_game();
  bool r = true;
  for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
    r = r && test_equality_int(0, get_degree_dir(g, i,EAST), "pb number of bridges connected");
    r = r && test_equality_int(0, get_degree_dir(g, i,NORTH), "pb number of bridges connected");
    r = r && test_equality_int(0, get_degree_dir(g, i,SOUTH), "pb number of bridges connected");
    r = r && test_equality_int(0, get_degree_dir(g, i,WEST), "pb number of bridges connected");
  }
  
  add_bridge_dir(g, 0, EAST);
    r = r && test_equality_int(1, get_degree_dir(g, 0, EAST), "pb number of bridges connected");
    
  add_bridge_dir(g, 1, SOUTH);
  r = r && test_equality_int(1, get_degree_dir(g, 1, SOUTH), "pb number of bridges connected");
  
  add_bridge_dir(g, 3, WEST);
  r = r && test_equality_int(1, get_degree_dir(g, 3, WEST), "pb number of bridges connected");
  
  add_bridge_dir(g, 1, NORTH);
  r = r && test_equality_int(1, get_degree_dir(g, 1, NORTH), "pb number of bridges connected");
  
  delete_game(g);
  return r;
}

bool test_del_bridge_dir () {
  game g = default_game();
  bool r = true;
  add_bridge_dir(g, 0, EAST);
  del_bridge_dir(g, 0, EAST);
  r = r && test_equality_int(0, get_degree_dir(g, 0, EAST), "pb number of bridges connected");
  add_bridge_dir(g, 1, NORTH);
  add_bridge_dir(g, 1, NORTH);
  del_bridge_dir(g, 1, NORTH);
  r = r && test_equality_int(1, get_degree_dir(g, 1, NORTH), "pb number of bridges connected");
  add_bridge_dir(g, 1, SOUTH);
  add_bridge_dir(g, 1, SOUTH);
  del_bridge_dir(g, 1, SOUTH);
  del_bridge_dir(g, 1, SOUTH);
  r = r && test_equality_int(0, get_degree_dir(g, 1, SOUTH), "pb number of bridges connected");
  r = r && test_equality_int(0, get_degree_dir(g, 0, NORTH), "pb number of bridges connected");
  delete_game(g);
  return r;
}

bool test_copy_game() {
  game g = default_game();
  bool r = true;
  game cp = copy_game(g);
  r = r && test_equality_int(game_nb_nodes(g), game_nb_nodes(cp), "Pb  with copy_game.\n");
  
  for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
    node cp_node = game_node(cp,i);
    r = r && test_equality_int(vals[i][0], get_x(cp_node), "Pb with x coord of copy_game.\n");
    r = r && test_equality_int(vals[i][1], get_y(cp_node), "Pb with y coord of copy_game.\n");
    r = r && test_equality_int(vals[i][2], get_required_degree(cp_node), "Pb with node's degree of copy_game.\n");
  }
  delete_game(cp);
  delete_game(g);
  return r;
}

bool test_game_over() {
  game g = default_game();
  bool r = true;
  r = r && test_equality_bool(false, game_over(g), "Pb with game_over.\n");
  add_bridge_dir(g, 0, NORTH);
  
  add_bridge_dir(g, 0, NORTH);
  add_bridge_dir(g, 1, NORTH);
  add_bridge_dir(g, 1, NORTH);
  add_bridge_dir(g, 1, EAST);
  add_bridge_dir(g, 0, EAST);
  add_bridge_dir(g, 4, EAST);
  add_bridge_dir(g, 4, EAST);
  add_bridge_dir(g, 6, SOUTH);
  r = r && test_equality_bool(true, game_over(g), "Pb with game_over.\n");
  del_bridge_dir(g, 0, NORTH);
  r = r && test_equality_bool(false, game_over(g), "Pb with game_over.\n");

  delete_game(g);
  return r;
}

bool test_add_bridge() {
  game g = default_game();
  bool r = true;
  
  add_bridge_dir(g, 0, EAST);
  r = r && test_equality_bool(1, get_degree_dir(g, 0, EAST),"Pb with add_bridge.\n");
  
  add_bridge_dir(g, 0, EAST);
  r = r && test_equality_bool(2, get_degree_dir(g, 0, EAST),"Pb with add_bridge.\n");
  
  add_bridge_dir(g, 1, NORTH);
  r = r && test_equality_bool(1, get_degree_dir(g, 1, NORTH),"Pb with add_bridge.\n");
  add_bridge_dir(g, 1, SOUTH);
  r = r && test_equality_bool(1, get_degree_dir(g, 1, SOUTH),"Pb with add_bridge.\n");
  
  add_bridge_dir(g, 3, WEST);
  r = r && test_equality_bool(1, get_degree_dir(g, 3, WEST),"Pb with add_bridge.\n");

  delete_game(g);
  return r;
}

bool test_game_node() {
  game g = default_game();
  bool r = true;
  for (int i = 0 ; i < EXAMPLE_NB_NODE; i++) {
    node n = game_node(g, i);
  
    r = r && test_equality_bool(get_x(n), vals[i][0], "Pb with x coord of game_node.\n");
    r = r && test_equality_bool(get_y(n), vals[i][1], "Pb with y coord of game_node.\n");
    r = r && test_equality_bool(get_required_degree(n), vals[i][2], "Pb with degree of game_node.\n");
  }
  return r;
}


bool test_game_nb_nodes() {
  game g = default_game();

  return test_equality_bool(EXAMPLE_NB_NODE, game_nb_nodes(g), "Pb with game_nb_nodes.\n");
}


int main (int argc, char *argv[])
{
  bool result= true;
  
  result = result && test_get_neighbour();
  result = result && test_get_node_number();
  
  result = result && test_can_add_bridge_dir();
  result = result && test_add_bridge();
  
  result = result && test_get_degree();
  result = result && test_get_degree_dir ();
  
  result = result && test_del_bridge_dir();
  result = result && test_game_node();
  
  result = result && test_game_nb_nodes();
  result = result && test_copy_game();
  
  result = result && test_game_over();
  
  if (result) {
    printf("OK\n");
    return EXIT_SUCCESS;
  }
  else {
    printf("ERROR\n");
    return EXIT_FAILURE;
  }
}
