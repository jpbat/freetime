/*
 *      sudoku.c
 *
 *      Copyright 2011 João Ferreira <joao@void>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int matrix[9][9];

void show()
{
    int i, j;

    for (i = 0; i < 9; ++i)
    {
        if (i % 3 == 0)
                printf("+-----------------------+\n");
        printf("| ");

        for (j = 0; j < 9; ++j) {

            if (j % 3 == 0 && j != 0)
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
    for (i = 0; i < 9; i++) {
        if (matrix[i][y] == temp || matrix[x][i] == temp) {
            return false;
        }
    }

    /* check squares */
    int X = x / 3;
    int Y = y / 3;

    int j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (matrix[X*3+i][Y*3+j] == temp) {
                return false;
            }
        }
    }

    return true;
}

void solve(int x, int y) {

    int i;

    if (y == 9) {
        x++;
        y = 0;
    }

    if (matrix[x][y] == 0) {

        for (i = 1; i <= 9; ++i) {

            if (canbe(i, x, y)) {

                matrix[x][y] = i;

                if (x == 8 && y == 8) {
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
        if (x == 8 && y == 8) {
            printf("\tFinal:\n");
            show();
            exit(0);
        }
        solve(x, y+1);
    }
}

int main(int argc, char** argv) {

    int i, j;

    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            scanf("%d", &matrix[i][j]);

    printf("\tInitial:\n");
    show();
    solve(0, 0);
    printf("Impossible to solve\n");

	return 0;
}
