// Fibonacci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
int my_fib(int ord){
	if (ord == 0) return 0;
	if (ord == 1) return 1;

	return my_fib(ord - 1) + my_fib(ord - 2);
	
}

void main()
{
	int ord=-1, ans;
	printf("enter desired order of Fibonacci number (a non-negative number):\n");
	while (ord < 0) {
		scanf_s("%d", &ord);
		if (ord < 1) printf("Desired order is not a positive number. Please enter again.\n");
	}
	
	ans = my_fib(ord);
	printf("The Fibonacci number of order %d is: %d\n", ord, ans);
    return;
}

*/

// And now in assembly:

char enterstr[] = "enter desired order of Fibonacci number (a non-negative number):\n";
char scanstr[] = "%d";
char notvalidnumber[] = "Desired order is not a positive number. Please enter again.\n";
char resultstr[] = "The Fibonacci number of order %d is: %d\n";

__declspec(naked) int my_fib(int ord) {
	_asm {
		push    ebp
		mov     ebp, esp
		push	ebx
		mov		eax, 08h[ebp]; eax = ord
		cmp		eax, 1
		je		_eqone
		cmp		eax, 0
		je		_eqzero;if not 0 or 1, continue:
		mov		ebx, eax; need two varaibles for the recursion
		push	eax; push ord
		sub		eax, 1
		push	eax; push(ord - 1)
		call	my_fib; myfib(ord - 1)
		add		esp, 4
		push	eax;push my_fib(ord-1)
		sub		ebx,2
		push	ebx
		call	my_fib;my_fib(ord-2)-->eax=my_fib(ord-2)
		add		esp,4
		pop		ebx;ebx=my_fib(ord-1)
		pop		edx;edx=ord
		add		eax,ebx ; eax= my_fib(ord - 1)+ my_fib(ord - 2)
		pop		ebx
		pop		ebp
		ret
		_eqzero:
		mov		eax,0
		pop		ebx
		pop		ebp
		ret
		_eqone:
		mov		eax, 1
		pop		ebx
		pop		ebp
		ret
	}
}

__declspec(naked) int main() {
	_asm {
		push    ebp
		mov     ebp, esp
		sub		esp, 04h	; Allocate space for ord
		_rescanf1:
		push    OFFSET enterstr		; "enter desired order of Fibonacci number (a non-negative number):\n";
		call	printf
		add		esp, 04h; clean stack
		lea     eax, [ebp - 04h]; pointer to ord
		push    eax
		push    OFFSET scanstr ;"%d"
		call	scanf
		add		esp, 8
		mov     eax, [ebp - 04h]; pointer to ord
		cmp		eax,00h				;check that the integer is non-negative
		jge		_isnonneg
		push    OFFSET notvalidnumber; "Desired order is not a positive number. Please enter again.\n";
		call	printf
		add		esp, 04h; clean stack
		jmp		_rescanf1
		_isnonneg:
		mov     eax, [ebp - 04h]; pointer to ord
		push	eax
		call	my_fib
		add		esp,4
		push	eax
		mov     edx, [ebp - 04h];  ord
		push	edx
		push    OFFSET resultstr; "The Fibonacci number of order %d is: %d\n"
		call	printf
		add		esp, 0Ch		;8 for the printf, 4 for cleaning the initial stack
		mov		eax, 0
		pop		ebp
		ret
	}
}