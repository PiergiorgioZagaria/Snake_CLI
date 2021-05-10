#include "engine.h"
#include "list_funcs.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void show(char grid[][W + 3]) {
  int i, j;
  for (i = 0; i < H + 2; i++) {
    for (j = 0; j < W + 2; j++) {
      // printf("%c", grid[i][j]);
      switch (grid[i][j]) {
      case ' ':
        printf(" ");
        break;
      case '#':
        printf(GREEN "#" RESET);
        break;
      case '?':
        printf(CYAN "?" RESET);
        break;
      default:
        printf(RED "%c" RESET, grid[i][j]);
      }
    }
    printf("\n");
  }
}

void create_grid(char grid[][W + 1 + 2]) {
  int i, j;
  printf(CLEAR);
  // Initialize grid
  for (i = 0; i < H + 2; i++) {
    for (j = 0; j < W + 2; j++) {
      grid[i][j] = ' ';
    }
  }
  for (i = 0; i < W + 2; i++) {
    grid[0][i] = '#';
    grid[H + 1][i] = '#';
  }
  for (j = 0; j < H + 2; j++) {
    grid[j][0] = '#';
    grid[j][W + 1] = '#';
    grid[j][W + 2] = '\0';
  }
}

void initialize_player(char grid[][W + 1 + 2], int *x, int *y, vec *vtmp,
                       Ptr_node *player, int *orientation, vec *point,char* input) {
  srand(time(NULL));

  *x = 10 + (rand() % (W - 20));
  *y = 5 + (rand() % (H - 10));
  vtmp->x = *x;
  vtmp->y = *y;
  *player = inserisciInTesta(*player, *vtmp);
  *orientation = rand() % 4;

  if (*orientation == UP) {
    grid[*y][*x] = '@';
    grid[*y + 1][*x] = '*';
    vtmp->y = *y + 1;
	*input = 'w';
  } else if (*orientation == RIGHT) {
    grid[*y][*x] = '@';
    grid[*y][*x - 1] = '*';
    vtmp->x = *x - 1;
	*input = 'd';
  } else if (*orientation == DOWN) {
    grid[*y][*x] = '@';
    grid[*y - 1][*x] = '*';
    vtmp->y = *y - 1;
	*input = 's';
  } else {
    grid[*y][*x] = '@';
    grid[*y][*x + 1] = '*';
    vtmp->x = *x + 1;
	*input = 'a';
  }
  *player = inserisciInTesta(*player, *vtmp);
  // Initialize point
  point->x = 1 + rand() % W;
  point->y = 1 + rand() % H;
  grid[point->y][point->x] = '?';
}

void show_options(char grid[][W + 1 + 2], int *len) {
  show(grid);
  printf("Quit: q\t: w\t: d\t: s\t: a\n\n");
  printf("Your score is: %d\n\n", *len - 2);
}

int move_player(Ptr_node *player, char *input, int *orientation, vec *point,
                int *len, vec *vtmp) {
  // Move player
  // First the body
  Ptr_node tmp = *player;
  while (tmp->next) {
    tmp->pos.x = tmp->next->pos.x;
    tmp->pos.y = tmp->next->pos.y;
    tmp = tmp->next;
  }
  // Then the head
  // TODO the player can go inside itself, left then right
  switch (*input) {
  case 'q':
    printf("\nYou quit the game, See you next time ( ͡ᵔ ͜ʖ ͡ᵔ ) \n");
    return 0;
  case 'w':
    *orientation = UP;
    break;
  case 'd':
    *orientation = RIGHT;
    break;
  case 's':
    *orientation = DOWN;
    break;
  case 'a':
    *orientation = LEFT;
    break;
  }
  switch (*orientation) {
  case UP:
    tmp->pos.y -= 1;
    break;
  case RIGHT:
    tmp->pos.x += 1;
    break;
  case DOWN:
    tmp->pos.y += 1;
    break;
  case LEFT:
    tmp->pos.x -= 1;
    break;
  }

  if (tmp->pos.x == point->x && tmp->pos.y == point->y) {
    point->x = 1 + rand() % W; // Spawn new point
    point->y = 1 + rand() % H;
    *len += 1; // Points + 1
    vtmp->x = (*player)->pos.x;
    vtmp->y = (*player)->pos.y;
    *player = inserisciInTesta(*player, *vtmp);
  }
  return 1;
}

void* get_input(void * args){
	use_args *actual_args = args;
	*(actual_args->my_char) = (char)getchar();
	printf("\nGot char\n");
	*(actual_args->got_char) = 1;
	free(actual_args);
}

void set_input(int* got_input,char* input,pthread_t *t1){
	if(*got_input){
		*got_input = 0;
		use_args *args = malloc(sizeof *args);
		args->my_char = input;
		args->got_char = got_input;
		if(pthread_create(t1,NULL,&get_input,args) != 0){
			printf("Err creazione thread\n");
			exit(1);
		}
	}
}
