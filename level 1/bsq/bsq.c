#include    "bsq.h"

char    *ft_strdup(char *str)
{
	char    *copia;
	int     i = 0;

	while (str[i])
		i++;
	copia = malloc(i + 1);
	if (!copia)
		return (NULL);
	i = 0;
	while (str[i])
	{
		copia[i] = str[i];
		i++;
	}
	copia[i] = '\0';

	return (copia);
}

int     leerCabecera(char *linea, ssize_t longitud, t_mapa *mapa)
{
	char	*puntero;

	if (linea[longitud - 1] == '\n')
		linea[--longitud] = 0;
	mapa->filas = atoi(linea);
	puntero = linea;
	while (*puntero >= '0' && *puntero <= '9')
		puntero++;
	if (*puntero != ' ')
		return (-1);
	mapa->vacio     = *(puntero + 1);
	mapa->obstaculo = *(puntero + 3);
	mapa->relleno   = *(puntero + 5);
	if (mapa->filas <= 0 || !mapa->vacio || !mapa->obstaculo || !mapa->relleno)
		return (-1);
	if (mapa->vacio == mapa->obstaculo || mapa->obstaculo == mapa->relleno || mapa->vacio == mapa->relleno)
		return (-1);
	
	return (0);
}

int     leerMapa(FILE *archivo, t_mapa *mapa)
{
	char	*linea = NULL;
	size_t	capacidad = 0;
	ssize_t	longitud;
	int		fila = 0;
	int		columna;

	mapa->columnas = -1;
	mapa->cuadricula = malloc(mapa->filas * sizeof(char *));
	if (!mapa->cuadricula)
		return (-1);
	while (fila < mapa->filas && (longitud = getline(&linea, &capacidad, archivo)) > 0)
	{
		if (linea[longitud - 1] == '\n')
			linea[--longitud] = 0;
		if (mapa->columnas == -1)
			mapa->columnas = longitud;
		else if (mapa->columnas != longitud)
			return (free(linea), -(fila + 1));
		columna = 0;
		while (columna < longitud)
		{
			if (linea[columna] != mapa->vacio && linea[columna] != mapa->obstaculo)
				return (free(linea), -(fila + 1));
			columna++;
		}
		mapa->cuadricula[fila] = ft_strdup(linea);
		if (!mapa->cuadricula[fila])
			return (free(linea), -(fila + 1));
		fila++;
		free(linea);
		linea = NULL;
		capacidad = 0;
	}
	free(linea);
	if (fila != mapa->filas || mapa->columnas <= 0)
		return (-(fila + 1));
	
	return (fila);
}

void    resolver(t_mapa *mapa)
{
	int	**dp;
	int	mejor_tam;
	int	mejor_fila;
	int	mejor_col;
	int	fila;
	int	col;
	int	minimo;

	mejor_tam = 0;
	mejor_fila = 0;
	mejor_col = 0;
	dp = calloc(mapa->filas, sizeof(int *));
	if (!dp)
		return ;
	fila = 0;
	while (fila < mapa->filas)
	{
		dp[fila] = calloc(mapa->columnas, sizeof(int));
		if (!dp[fila])
			return ;
		fila++;
	}
	fila = 0;
	while (fila < mapa->filas)
	{
		col = 0;
		while (col < mapa->columnas)
		{
			if (mapa->cuadricula[fila][col] == mapa->obstaculo)
				dp[fila][col] = 0;
			else if (fila == 0 || col == 0)
				dp[fila][col] = 1;
			else
			{
				minimo = dp[fila - 1][col] < dp[fila][col - 1]
					? dp[fila - 1][col] : dp[fila][col - 1];
				dp[fila][col] = (minimo < dp[fila - 1][col - 1]
					? minimo : dp[fila - 1][col - 1]) + 1;
			}
			if (dp[fila][col] > mejor_tam)
			{
				mejor_tam  = dp[fila][col];
				mejor_fila = fila;
				mejor_col  = col;
			}
			col++;
		}
		fila++;
	}
	if (mejor_tam > 0)
	{
		fila = mejor_fila - mejor_tam + 1;
		while (fila <= mejor_fila)
		{
			col = mejor_col - mejor_tam + 1;
			while (col <= mejor_col)
			{
				mapa->cuadricula[fila][col] = mapa->relleno;
				col++;
			}
			fila++;
		}
	}
	fila = 0;
	while (fila < mapa->filas)
	{
		free(dp[fila]);
		fila++;
	}
	free(dp);
}

int     ejecutarBSQ(FILE *archivo)
{
	char	*linea = NULL;
	ssize_t	longitud;
	size_t	capacidad = 0;
	int		fila = 0;
	int		filasLeidas;
	t_mapa	mapa;

	if ((longitud = getline(&linea, &capacidad, archivo)) <= 0)
		return (free(linea), -1);
	if (leerCabecera(linea, longitud, &mapa) == -1)
		return (free(linea), -1);
	free(linea);
	filasLeidas = leerMapa(archivo, &mapa);
	if (filasLeidas < 0)
	{
		while (fila < -(filasLeidas + 1))
			free(mapa.cuadricula[fila++]);
		free(mapa.cuadricula);
		return (-1);
	}
	resolver(&mapa);
	while (fila < filasLeidas)
	{
		fputs(mapa.cuadricula[fila], stdout);
		fputs("\n", stdout);
		free(mapa.cuadricula[fila]);
		fila++;
	}
	free(mapa.cuadricula);
	
	return (0);
}

int	executeBSQ(FILE *archivo)
{
	char	*linea = NULL;
	ssize_t	longitud;
	size_t	capacidad = 0;
	int		fila = 0;
	int		filasLeidas;
	t_mapa	mapa;
	
	if ((longitud = getline(&linea, &capacidad, archivo)) <= 0)
	return (free(linea), -1);
	if (leerCabecera(linea, longitud, &mapa) == -1)
	return (free(linea), -1);
	free(linea);
	filasLeidas = leerMapa(archivo, &mapa);
	if (filasLeidas < 0)
	{
		while (fila < -(filasLeidas + 1))
		free(mapa.cuadricula[fila++]);
		free(mapa.cuadricula);
		return (-1);
	}
	resolver(&mapa);
	while (fila < filasLeidas)
	{
		fputs(mapa.cuadricula[fila], stdout);
		fputs("\n", stdout);
		free(mapa.cuadricula[fila]);
		fila++;
	}
	free(mapa.cuadricula);
	
	return (0);
}

int     convertFile(char *ruta)
{
	FILE	*archivo;
	int		resultado;

	archivo = fopen(ruta, "r");
	if (!archivo)
		return (-1);
	resultado = executeBSQ(archivo);
	fclose(archivo);
	return (resultado);
}