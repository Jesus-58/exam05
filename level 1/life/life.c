#include "life.h"

void    print_board(char *board, int ancho, int alto)
{
    int index;

    index = 0;
    while (index < ancho * alto)
    {
        putchar(board[index] ? 'O' : ' ');
        index++;
        if(index % ancho == 0)
            putchar('\n');
    }
}
int count_vecinos(char *board, int ancho, int alto, int x, int y)
{
    int dx;
    int dy;
    int nx;
    int ny;
    int vecinos;

    dy = -1;
    vecinos = 0;
    while(dy <= 1)
    {
        dx = -1;
        while(dx <= 1)
        {
            nx = x + dx;
            ny = y + dy;
            if((dx != 0 || dy != 0) && nx >= 0 && nx < ancho && ny >= 0 && ny < alto)
                vecinos += board[ny * ancho + nx];
            dx++;
        }
        dy++;
    }
    return(vecinos);
}
void    apply_life(char *board, char *next_board, int ancho, int alto)
{
    int index;
    int vecinos;

    index = 0;
    vecinos = 0;
    while(index < ancho * alto)
    {
        vecinos = count_vecinos(board, ancho, alto, index % ancho, index / alto);
        next_board[index] = (board[index] && (vecinos == 2 || vecinos == 3)) || (!board[index] && vecinos == 3);
        index++; 
    }
    index = 0;
    while(index < ancho * alto)
    {
        board[index] = next_board[index];
        index++;
    }
}
int main(int argc, char **argv)
{
    int ancho;
    int alto;
    int iter;
    int x;
    int y;
    int pen_down;
    char    *board;
    char    *next_board;
    char c;

    if (argc != 4)
        return(0);
    ancho = atoi(argv[1]);
    alto = atoi(argv[2]);
    iter = atoi(argv[3]);
    if (iter < 0)
        iter = 0;
    board = calloc(ancho * alto + 1, 1);
    next_board = calloc(ancho * alto, 1);
    if(!board || !next_board)
        return(free(board), free(next_board), 0);
    x = 0;
    y = 0;
    pen_down = 0;
    while(read(0, &c, 1) > 0)
    {
        if(c == 'x')
            pen_down = !pen_down;
        if(c == 'w' && y > 0)
            y--;
        if(c == 's' && y < alto - 1)
            y++;
        if(c == 'a' && x > 0)
            x--;
        if(c == 'd' && x < ancho - 1)
            x++;
        if(pen_down)
            board[y * ancho + x] = 1;
    }
    while(iter--)
        apply_life(board, next_board, ancho, alto);
    print_board(board, ancho, alto);
    free(board);
    free(next_board);
    return(0);
}