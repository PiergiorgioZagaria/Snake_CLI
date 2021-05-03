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

void show(char grid[][W + 3]);
void create_grid(char grid[][W + 1 + 2]);
#endif
