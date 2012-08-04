/*
 *      Chess.c
 *
 *      Copyright 2012 João Ferreira <jpbat@student.dei.uc.pt>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define WHITE 'w'
#define BLACK 'b'

typedef struct piece {
	char name;
	char color;
	int moves;
} piece;

piece table[8][8];
int turn = 0;

void draw()
{
	int i, j, k;
	char blank;
	system("cls");

	printf("   ");
	for (i = 0; i < 8; i++)
		printf("    %c  ", 'a'+i);
	printf("\n");
	for (i = 0; i < 8; i++)
	{
		printf("   ---------------------------------------------------------\n");
		for (k = 0; k < 3; k++)
		{
			if (k == 1)
				printf("%d  ", i+1);
            else
                printf("   ");

			for (j = 0; j < 8; j++)
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
						blank = ' ';
					else
						blank = '+';
				}
				else
				{
					if (j % 2 != 0)
						blank = ' ';
					else
						blank = '+';
				}

				printf("|");

				if (k == 1)
				{
					if (table[i][j].color != 0)
						printf("%c %c%c %c", blank, table[i][j].color, table[i][j].name,  blank);
					else
						printf("%c%c%c%c%c%c", blank, blank, blank, blank, blank, blank);
				}
				else
					printf("%c%c%c%c%c%c", blank, blank, blank, blank, blank, blank);
			}

			printf("|");

			if (k == 1)
				printf("  %d", 1+i);
            else
                printf("   ");
			printf("\n");
		}
	}
	printf("   ---------------------------------------------------------\n");
	printf("   ");
	for (i = 0; i < 8; i++)
		printf("    %c  ", i+'a');
	printf("\n");
}

char oposite(char c)
{
	if (c == WHITE)
		return BLACK;
	return WHITE;
}

bool checkPawnMove(int oldX, int oldY, int newX, int newY)
{
    if (table[oldX][oldY].color == WHITE && newX > oldX)
        return false;

    if (table[oldX][oldY].color == BLACK && newX < oldX)
        return false;

	if (abs(newX - oldX) > 2)
		return false;

	if (abs(newX - oldX) == 2 && table[oldX][oldY].moves > 0)
		return false;

	if (abs(newY - oldY) > 1)
		return false;

	if (newY != oldY && table[newX][newY].color != oposite(table[oldX][oldY].color))
		return false;

	return true;
}

bool checkRookMove(int oldX, int oldY, int newX, int newY)
{
	if (newX != oldX && newY != oldY)
		return false;

	int i;
	if (newY == oldY)
	{
		if (newX > oldX)
			for (i = oldX+1; i < newX; i++)
				if (table[i][oldY].name != 0)
					return false;
		else
			for (i = newX+1; i < oldX; i++)
				if (table[i][oldY].name != 0)
					return false;
	}
	else
	{
		if (newY > oldY)
			for (i = oldY+1; i < newY; i++)
				if (table[oldX][i].name != 0)
					return false;
		else
			for (i = newY+1; i < oldY; i++)
				if (table[oldX][i].name != 0)
					return false;
	}

	return true;
}

bool checkHorseMove(int oldX, int oldY, int newX, int newY)
{
	if (newX == oldX + 1 && newY == oldY + 2)
		return true;

	if (newX == oldX + 1 && newY == oldY - 2)
		return true;

	if (newX == oldX - 1 && newY == oldY + 2)
		return true;

	if (newX == oldX - 1 && newY == oldY - 2)
		return true;

	if (newX == oldX + 2 && newY == oldY + 1)
		return true;

	if (newX == oldX + 2 && newY == oldY - 1)
		return true;

	if (newX == oldX - 2 && newY == oldY + 1)
		return true;

	if (newX == oldX - 2 && newY == oldY - 1)
		return true;

	return false;
}

bool checkBishopMove(int oldX, int oldY, int newX, int newY)
{
	if (abs(oldX-newX) != abs(oldY-newY))
		return false;

	int i;
	if (newX > oldX)
	{
		if (newY > oldY)
			for (i = 1 ; i < newY-oldY ; i++)
				if (table[oldX+i][oldY+i].color != 0)
					return false;
		else
			for (i = 1 ; i < newY-oldY ; i++)
				if (table[oldX+i][oldY-i].color != 0)
					return false;
	}
	else
	{
		if (newY > oldY)
			for (i = 1 ; i < newY-oldY ; i++)
				if (table[oldX-i][oldY+i].color != 0)
					return false;
		else
			for (i = 1 ; i < newY-oldY ; i++)
				if (table[oldX-i][oldY-i].color != 0)
					return false;
	}

	return true;
}

bool checkQueenMove(int oldX, int oldY, int newX, int newY)
{
	return checkBishopMove(oldX, oldY, newX, newY) || checkRookMove(oldX, oldY, newX, newY);
}

bool checkKingMove(int oldX, int oldY, int newX, int newY)
{
	if (newX == oldX + 1 && newY == oldY)
		return true;

	if (newX == oldX + 1 && newY == oldY + 1)
		return true;

	if (newX == oldX + 1 && newY == oldY - 1)
		return true;

	if (newX == oldX && newY == oldY + 1)
		return true;

	if (newX == oldX && newY == oldY - 1)
		return true;

	if (newX == oldX - 1 && newY == oldY + 1)
		return true;

	if (newX == oldX - 1 && newY == oldY - 1)
		return true;

	if (newX == oldX - 1 && newY == oldY)
		return true;

	return false;
}

bool legal(int oldX, int oldY, int newX, int newY, char cmd)
{
    if (newX > 7 || newX < 0 || newY > 7 || newY < 0)
		return false;

	if (table[newX][newY].color == table[oldX][oldY].color)
		return false;

	char name = table[oldX][oldY].name;

	if (name == 0)
		return false;

	char color = table[oldX][oldY].color;
	if (color == WHITE && turn % 2 != 0 || color == BLACK && turn % 2 == 0)
		return false;

    if (name != cmd)
        return false;

	switch(name)
	{
		case 'P':
			return checkPawnMove(oldX, oldY, newX, newY);
		case 'R':
			return checkRookMove(oldX, oldY, newX, newY);
		case 'H':
			return checkHorseMove(oldX, oldY, newX, newY);
		case 'B':
			return checkBishopMove(oldX, oldY, newX, newY);
		case 'Q':
			return checkQueenMove(oldX, oldY, newX, newY);
		case 'K':
			return checkKingMove(oldX, oldY, newX, newY);
		default:
			printf("ERROR %c\n", name);
			exit(0);
	}
}

void move()
{
	int oldX, oldY, newX, newY;
	char move[64];

	do
	{
		draw();

		printf("Your move: ");
		scanf("%s", move);

		oldX = move[2]-'0'-1;
		oldY = move[1]-'a';

		newX = move[4]-'0'-1;
		newY = move[3]-'a';

	} while( legal(oldX, oldY, newX, newY, move[0]) == false );

	table[newX][newY].color = table[oldX][oldY].color;
	table[newX][newY].name = table[oldX][oldY].name;
	table[newX][newY].moves = table[oldX][oldY].moves+1;

	table[oldX][oldY].color = table[oldX][oldY].name = table[oldX][oldY].moves = 0;
}

void game()
{
	int option;

	while(1)
	{
		draw();

		if (turn % 2 == 0)
			printf("Player 1\n");
		else
			printf("Player 2\n");

		printf("1. Move\n");
		printf("2. Give Up\n");

		scanf("%d", &option);

		switch(option)
		{
			case 1:
				move();
				break;
			case 2:
				printf("Player %d win after %d turns!\n", !(turn % 2)+1, turn);
				return;
		}

		//turn++;
	}
}

void init()
{
	int i, j;

	memset(table, 0, 8*8*sizeof(piece));

	/* whites */
	for (i = 0; i < 8; i++)
		table[6][i].name = 'P';

	table[7][0].name = table[7][7].name = 'R';
	table[7][1].name = table[7][6].name = 'H';
	table[7][2].name = table[7][5].name = 'B';
	table[7][3].name = 'Q';
	table[7][4].name = 'K';

	for (i = 6; i < 8; i++)
		for (j = 0; j < 8; j++)
			table[i][j].color = WHITE;

	/* black */
	for (i = 0; i < 8; i++)
		table[1][i].name = 'P';

	table[0][0].name = table[0][7].name = 'R';
	table[0][1].name = table[0][6].name = 'H';
	table[0][2].name = table[0][5].name = 'B';
	table[0][3].name = 'Q';
	table[0][4].name = 'K';

	for (i = 0; i < 2; i++)
		for (j = 0; j < 8; j++)
			table[i][j].color = BLACK;
}

int main(int argc, char** argv)
{
	int i, j;

	init();

	//game();
	printf("♔\n");
	return 0;
}
