#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#       sudoku.py
#       
#       Copyright 2012 João Ferreira <jpbat@student.dei.uc.pt>
#

import turtle
import sys

table = [[0 for i in range(6)] for i in range(5)]

def move(x, y):
	turtle.up()
	turtle.goto(x, y)
	turtle.down()

def grid(side):
	turtle.color("blue")
	#horizontal
	for i in range(1, 5):
		move(-side*3, side*3-i*side)
		turtle.fd(6*side)

	#vertical
	turtle.setheading(-90)
	for i in range(1, 6):
		move(-side*3+i*side, side*3)
		turtle.fd(5*side)
	
	#big square
	turtle.color("red")
	turtle.width(2)
	turtle.setheading(0)
	move(-side*3, side*3)
	for i in range(4):
		if (i % 2 == 0):
			cena = side * 6
		else:
			cena = side * 5
		turtle.fd(cena)
		turtle.rt(90)

def write(side):
	turtle.color("green")
	for i in range(5):
		for j in range(6):
			move(-side*5/2.+j*side, side*6/2.-(i+1)*side)
			turtle.write(table[i][j], align="center", font=("Arial", side/2, "bold"))
	return

def show():
	turtle.hideturtle()
	turtle.speed(0)
	side = turtle.window_height()/7
	grid(side)
	write(side)
	turtle.exitonclick()

def solve(x, y, number):

	if x >= 5 or x < 0 or y >= 6 or y < 0 or table[x][y] != 0:
		if number == 31:
			show()
		return

	table[x][y] = number
	solve(x+3, y, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x-3, y, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x, y+3, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x, y-3, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x+2, y+2, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x+2, y-2, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x-2, y+2, number+1)
	table[x][y] = 0

	table[x][y] = number
	solve(x-2, y-2, number+1)
	table[x][y] = 0

def main():
	xInit = 0
	yInit = 0
	solve(xInit, yInit, 1)

if __name__ == '__main__':
	main()