#ifndef LIFE_H
#define LIFE_H

#include    <unistd.h>
#include    <stdio.h>
#include    <stdlib.h>

void    applyLife(char *board, char *nextboard, int ancho, int alto);
int     countVecinos(char *board, int ancho, int alto, int x, int y);
void    printBoard(char *board, int ancho, int alto);

#endif