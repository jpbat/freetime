#!/usr/bin/env python
# -*- coding: utf-8 -*-

def solve(numbers):

	_3 = -1
	_m = -1

	for i in xrange(len(numbers)):

		if numbers[i] > numbers[_3] and numbers[i] % 3 == 0 or _3 == -1 and numbers[i] % 3 == 0:
			_3 = i
			continue

		if numbers[i] > numbers[_m] or _m == -1:
			_m = i

	if _3 == -1 or len(numbers) < 2:
		return 'No solution'

	return 'Solution: ' + str(numbers[_m]) + '*' + str(numbers[_3]) + ' = ' + str(numbers[_m]*numbers[_3])

def main():
	
	numbers = []
	info = raw_input('insert numbers: ').split()
	
	for l in info:
		numbers.append(int(l))

	print solve(numbers)

if __name__ == '__main__':
	main()
