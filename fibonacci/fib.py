#!/bin/python3

fib_nums = [1, 1]

def fib(n):
	if n < 2: return 1
	if n == len(fib_nums):
		fib_nums.append(fib_nums[n - 1] + fib_nums[n - 2])
	else:
		return fib(n - 1) + fib(n - 2)
	return fib_nums[n]

try:
	number = int(input("Enter number: "))
except:
	print("Invalid type")
	exit()

assert not number < 0, "Bad value ({}) - number cannot be less than 0".format(number)

# n - 1 is for natural representation just like order start with 1
# otherwise it is like it starts with 0
print("fin({}):".format(number), fib(number - 1))
