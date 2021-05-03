#include "engine.h"

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
