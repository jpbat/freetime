#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#       sudoku.py
#       
#       Copyright 2012 João Ferreira <jpbat@student.dei.uc.pt>
#

import sys
import turtle
import math

squares = 9
matrix = [[0 for i in range(squares)] for i in range (squares)]
initial = []

def fits(temp, x, y):
	#testing for columns and lines
	for i in range(squares):
		if matrix[i][y] == temp or matrix[x][i] == temp:
			return False

	sqrt = int(math.sqrt(squares))

	#testing for squares
	X = x / sqrt
	Y = y / sqrt

	for i in range(sqrt):
		for j in range(sqrt):
			if matrix[X*sqrt+i][Y*sqrt+j] == temp:
				return False

	return True

def end():
	show()
	sys.exit()

def solve(x, y):

	if y == squares:
		x += 1
		y = 0

	if matrix[x][y] == 0:
		for i in range(1,squares+1):
			if fits(i, x, y):
				matrix[x][y] = i

				if x == squares-1 and y == squares-1:
					end()

				solve(x, y+1)
				matrix[x][y] = 0

	else:
		if x == squares-1 and y == squares-1:
			end()
		solve(x, y+1)

def move(x, y):
	turtle.up()
	turtle.goto(x, y)
	turtle.down()

def grid(side):

	sqrt = math.sqrt(squares)

	#horizontal
	for i in range(1,squares):
		if i % sqrt == 0:
			turtle.width(2)
			turtle.color("red")
		move(-side*squares/2., side*squares/2.-i*side)
		turtle.fd(side*squares)
		turtle.width(1)
		turtle.color("black")

	#vertical
	turtle.setheading(-90)
	for i in range(1,squares):
		if i % sqrt == 0:
			turtle.width(2)
			turtle.color("red")
		move(-side*squares/2.+i*side, side*squares/2.)
		turtle.fd(side*squares)
		turtle.width(1)
		turtle.color("black")

	#big square
	move(-side*squares/2., side*squares/2.)
	turtle.width(3)
	turtle.setheading(0)
	turtle.color("blue")
	for i in range(4):
		turtle.fd(side*squares)
		turtle.rt(90)

def draw(side):
	turtle.speed(0)
	turtle.hideturtle()
	grid(side)

def write(side):
	turtle.color("black")
	for i in range(squares):
		for j in range(squares):
			move(-side*squares/2.+side/2+j*side, side*squares/2.-.875*side-i*side)
			if (i,j) in initial:
				turtle.color("black")
			else:
				turtle.color("green")
			turtle.write(matrix[i][j], align="center", font=("Arial", side/2, "bold"))

def show():
	#adjust stuff size accordingly to window size
	side = turtle.window_height()/(squares+1)
	draw(side)
	write(side)
	turtle.exitonclick()

def main():
	for i in range(squares):
		temp = raw_input().split()
		for j in range(squares):
			matrix[i][j] = int(temp[j])
			if matrix[i][j]:
				initial.append((i,j))
				
	solve(0,0)
	return 0

if __name__ == '__main__':
	main()
