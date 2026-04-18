#ifndef LIFE_H
# define LIFE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    apply_life(char *board, char *next_board, int ancho, int alto);
int count_vecinos(char *board, int ancho, int alto, int x, int y);
void    print_board(char *board, int ancho, int alto);

#endif