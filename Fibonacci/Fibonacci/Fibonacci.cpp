// Fibonacci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int my_fib(int ord){
	if (ord == 0) return 0;
	if (ord == 1) return 1;

	return my_fib(ord - 1) + my_fib(ord - 2);
	
}

int main()
{
	int ord=-1, ans;
	printf("enter desired order of Fibonacci number (a non-negative number):\n");
	while (ord < 0) {
		scanf_s("%d", &ord);
		if (ord < 1) printf("Desired order is not a positive number. Please enter again.\n");
	}
	
	ans = my_fib(ord);
	printf("The Fibonacci number of order %d is: %d\n", ord, ans);
    return 0;
}

