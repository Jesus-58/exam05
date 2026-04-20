#ifndef LIFE_H
#define	LIFE_H

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>

void	applyLife(char *board, char *nextBoard, int ancho, int alto);
int		countVecinos(char *board, int ancho, int alto, int x, int y);
void	printBoard(char *board, int ancho, int alto);

#endif