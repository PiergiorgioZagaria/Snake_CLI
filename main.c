#include "engine.h"
#include "list_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* TODO
 * Use select
 * Implement settings
 * Implement leaderboard
 * Implement colors
 */
int main() {
  char grid[H + 2][W + 1 + 2]; // Grid
  int play = 1;                // Game loop
  int i, j;                    // Iterators
  Ptr_node player = NULL;      // Player position
  int x, y;
  vec vtmp;
  int orientation;
  int len = 2; // Starting len
  vec point;   // The position of the point
  srand(time(NULL));

  // Initialize grid
  create_grid(grid);

  // Initialize player between x:10,W-10 y:5,H-5
  x = 10 + (rand() % (W - 20));
  y = 5 + (rand() % (H - 10));
  vtmp.x = x;
  vtmp.y = y;
  player = inserisciInTesta(player, vtmp);
  orientation = rand() % 4;

  if (orientation == UP) {
    grid[y][x] = '@';
    grid[y + 1][x] = '*';
    vtmp.y = y + 1;
  } else if (orientation == RIGHT) {
    grid[y][x] = '@';
    grid[y][x - 1] = '*';
    vtmp.x = x - 1;
  } else if (orientation == DOWN) {
    grid[y][x] = '@';
    grid[y - 1][x] = '*';
    vtmp.y = y - 1;
  } else {
    grid[y][x] = '@';
    grid[y][x + 1] = '*';
    vtmp.x = x + 1;
  }
  player = inserisciInTesta(player, vtmp);
  // Initialize point
  point.x = 1 + rand() % W;
  point.y = 1 + rand() % H;
  grid[point.y][point.x] = '?';

  // Game loop
  while (play + 1) {
    show(grid);
    printf("Quit: 0\t: 1\t: 2\t: 3\t: 4\n\n");
    printf("Your score is: %d\n\n", len - 2);
    scanf("%d", &play);

    // Move player
    // First the body
    Ptr_node tmp = player;
    while (tmp->next) {
      tmp->pos.x = tmp->next->pos.x;
      tmp->pos.y = tmp->next->pos.y;
      tmp = tmp->next;
    }
    // Then the head
    switch (play - 1) {
    case -1:
      printf("\nYou quit the game, See you next time ( ͡ᵔ ͜ʖ ͡ᵔ ) \n");
      return 0;
    case UP:
      orientation = UP;
      break;
    case RIGHT:
      orientation = RIGHT;
      break;
    case DOWN:
      orientation = DOWN;
      break;
    case LEFT:
      orientation = LEFT;
      break;
    }
    switch (orientation) {
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

    if (tmp->pos.x == point.x && tmp->pos.y == point.y) {
      point.x = 1 + rand() % W; // Spawn new point
      point.y = 1 + rand() % H;
      len += 1; // Points + 1
      vtmp.x = player->pos.x;
      vtmp.y = player->pos.y;
      player = inserisciInTesta(player, vtmp);
    }

    // Update the grid
    // First clear the grid
    for (i = 0; i < H; i++) {
      for (j = 0; j < W; j++) {
        grid[i + 1][j + 1] = ' ';
      }
    }

    // Then draw player
    tmp = player;
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
  return 0;
}
