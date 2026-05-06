#ifndef BSQ_H
# define	BSQ_H

#include	<stdio.h>
#include	<stdlib.h>

typedef struct	s_mapa
{
	char	**cuadricula;
	int		filas;
	int		columnas;
	char	vacio;
	char	relleno;
	char	obstaculo;
} t_mapa;

char	*ft_strdup(char *str);
int		leerCabecera(char *line, ssize_t longitud, t_mapa *mapa);
int		leerMapa(FILE *archivo, t_mapa *mapa);
void	resolver(t_mapa *mapa);
int		executeBSQ(FILE *archivo);
int		convertFile(char *ruta);

#endif
