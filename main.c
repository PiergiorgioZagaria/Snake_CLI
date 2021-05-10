#include "engine.h"
#include "list_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
/* TODO
 * Implement Input
 * Implement settings
 * Implement leaderboard
 * Implement colors
 */

typedef struct {
	char* my_char;
	int*  got_char;
} use_args;

void* get_input(void * args){
	use_args *actual_args = args;
	*(actual_args->my_char) = (char)getchar();
	printf("\nGot char\n");
	*(actual_args->got_char) = 1;
	free(actual_args);
}

int main() {
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

    // TODO Input
    /* if (scanf("%c", &input) == 0) { */
    /*   printf("Can't accept that key\n"); */
    /*   return 1; */
    /* } */
	if(got_input){
		got_input = 0;
		use_args *args = malloc(sizeof *args);
		args->my_char = &input;
		args->got_char = &got_input;
		if(pthread_create(&t1,NULL,&get_input,args) != 0){
			printf("Err creazione thread\n");
			return 1;
		}
	}

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
