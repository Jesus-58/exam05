#include    "life.h"

void    printBoard(char *board, int ancho, int alto)
{
    int index = 0;

    while (index < ancho * alto)
    {
        putchar (board[index] ? 'O' : ' ')
        index++;
        if (index % ancho == 0)
            putchar('\n');
    }
}

int countVecinos(char *board, int ancho, int alto, int x, int y)
{
    int dx, dy, nx, ny, vecinos;

    vecinos = 0;
    dy = -1;
    while (dy <= 1)
    {
        dx = -1
        while (dx <= 1)
        {
            nx = x + dx;
            ny = y + dy;
            if ((dx != 0 || dy != 0) && nx >= 0 && nx < ancho && ny >= 0 && ny < alto)
                vecinos += board[ny * ancho + nx];
            dx++;
        }
        dy++;
    }
    return (vecinos);
}

void    applyLife(char *board, char *nextBoard, int ancho, int alto)
{
    int index, vecinos;

    index = 0;
    vecinos = 0;
    while (index < ancho * alto)
    {
        vecinos = countVecinos(board, ancho, alto, index % ancho, index / alto);
        nextBoard[index] = (board[index] && (vecinos == 2 || vecinos == 3) || (!board[index] && vecinos == 3));
        index++;
    }
    index = 0;
    while (index < ancho * alto)
    {
        board[index] = nextBoard[index];
        index++;
    }
}

int main(int argc, char **argv)
{
    int ancho, alto, iter, x, y, penDown;
    char *board;
    char *nextBoard;
    char c;

    if (argc != 4)
        return (0);
    ancho = atoi(argv[1]);
    alto = atoi(argv[2]);
    iter = atoi(argv[3]);
    if (iter < 0)
        iter = 0;

    board = calloc(ancho * alto + 1, 1);
    nextBoard = calloc(ancho * alto, 1);
    if (!board || !nextBoard)
        return (free(board), free(nextBoard), 0);

    x = 0;
    y = 0;
    penDown = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == 'x')
            penDown = !penDown;
        if (c == 'w' && y > 0)
            y--;
        if (c == 's' && y < alto - 1)
            y++;
        if (c == 'a' && x > 0)
            x--;
        if (c == 'd' && x < ancho - 1)
            x++;
        if (penDown)
            board[y * ancho + x] = 1;
    }

    while (iter--)
        applyLife(board, nextBoard, ancho, alto);
    printBoard(board, ancho, alto);
    free(board);
    free(nextBoard);
    return (0);
}