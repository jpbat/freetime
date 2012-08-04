/*
 *      sudoku.c
 *
 *      Copyright 2011 João Ferreira <joao@void>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define squares 36

int sqr = 6;
int matrix[squares][squares];
bool found = false;

void show()
{
    int i, j;

    for (i = 0; i < squares; ++i)
    {
        if (i % sqr == 0)
                printf("+-----------------------+\n");
        printf("| ");

        for (j = 0; j < squares; ++j) {

            if (j % sqr == 0 && j != 0)
                printf("| ");

            if (matrix[i][j] == 0)
                printf("- ");
            else
                printf("%d ", matrix[i][j]);
        }
        printf("|\n");
    }
    printf("+-----------------------+\n");

}

bool canbe(int temp, int x, int y) {

    int i;

    /* check columns and lines*/
    for (i = 0; i < squares; i++) {
        if (matrix[i][y] == temp || matrix[x][i] == temp) {
            return false;
        }
    }

    /* check squares */
    int X = x / sqr;
    int Y = y / sqr;

    int j;
    for (i = 0; i < sqr; ++i) {
        for (j = 0; j < sqr; ++j) {
            if (matrix[X*sqr+i][Y*sqr+j] == temp) {
                return false;
            }
        }
    }

    return true;
}

void solve(int x, int y) {

    int i;

    if (y == squares) {
        x++;
        y = 0;
    }

    if (matrix[x][y] == 0) {

        for (i = 1; i <= squares; ++i) {

            if (canbe(i, x, y)) {
                
                matrix[x][y] = i;

                if (x == squares-1 && y == squares-1) {
                    printf("\tFinal:\n");
                    show();
                    exit(0);
                }

                solve(x, y+1);
                matrix[x][y] = 0;
            }
        }
    }

    else {
        if (x == squares-1 && y == squares-1) {
            printf("\tFinal:\n");
            show();
            exit(0);
        }
        solve(x, y+1); 
    }
}

int main(int argc, char** argv) {

    int i, j;

    scanf("%d", &i);

    for (i = 0; i < squares; i++)
        for (j = 0; j < squares; j++)
            scanf("%d", &matrix[i][j]);

    printf("\tInitial:\n");
    show();

    solve(0, 0);

	return 0;
}
