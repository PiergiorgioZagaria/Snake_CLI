#include "game.h"
#include "engine.h"
#include "list_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
/* TODO
 * Implement settings
 * Implement leaderboard
 * Implement colors
 */

int main_game() {
  pthread_t t1;
  static struct termios oldt,newt;
  char input;                  // Input (called play before)
  int got_input = 1;
  char grid[H + 2][W + 1 + 2]; // Grid
  int i, j;                    // Iterators
  Ptr_node player = NULL;      // Player position
  int x, y;
  vec vtmp;
  int orientation;
  int len = 2; 				  // Starting len
  vec point;   				  // The position of the point

  tcgetattr(STDIN_FILENO,&oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON); 
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  // Initialize grid
  create_grid(grid);
  initialize_player(grid, &x, &y, &vtmp, &player, &orientation, &point,&input);

  // Game loop
  while (input != 'q') {

    show_options(grid, &len);

    set_input(&got_input,&input,&t1);

    if (!move_player(&player, &input, &orientation, &point, &len, &vtmp)) {
      return 0;
    }
    for (i = 0; i < H; i++) {
      for (j = 0; j < W; j++) {
        grid[i + 1][j + 1] = ' ';
      }
    }

    // Then draw player
    Ptr_node tmp = player;
    while (tmp->next) {
      grid[tmp->pos.y][tmp->pos.x] = '*';
      tmp = tmp->next;
    }
    grid[tmp->pos.y][tmp->pos.x] = '@';

    // Draw the point
    grid[point.y][point.x] = '?';

    usleep(100000);
    printf(CLEAR);
  }
  if(pthread_join(t1,NULL) != 0){
    printf("Err joining threads\n");
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return 0;
}
