#!/usr/bin/env python
# -*- coding: utf-8 -*-

def solve(numbers):

	numbers.sort(reverse=True)

	index = -1

	for i in xrange(len(numbers)):
		if numbers[i] % 3 == 0:
			index = i
			break

	if index == -1 or len(numbers) < 2:
		return 'No solution'

	if index == 0:
		return 'Solution: ' + str(numbers[0]) + '*' + str(numbers[1]) + ' = ' + str(numbers[0]*numbers[1])

	return 'Solution: ' + str(numbers[0]) + '*' + str(numbers[index]) + ' = ' + str(numbers[0]*numbers[index])

def main():
	
	numbers = []
	info = raw_input('insert numbers: ').split()
	
	for l in info:
		numbers.append(int(l))
	
	print solve(numbers)

if __name__ == '__main__':
	main()
