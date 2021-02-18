#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <stdio.h>
enum dir { UP, RIGHT, DOWN, LEFT };
#define W 50
#define H 25


#define CLEAR "\e[1;1H\e[2J"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BACKGROUND "\e[48;5;3m"

void show(char grid[][W + 3]) {
  int i,j;
  for (i = 0; i < H + 2; i++) {
    for(j = 0; j < W +2;j++){
      //printf("%c", grid[i][j]);
      switch(grid[i][j]){
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
          printf(RED "%c" RESET,grid[i][j]);
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
#endif
