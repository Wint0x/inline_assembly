#include <stdio.h>
#include <stdbool.h>

// C function 1 to check for even numbers
bool is_even_c_version1(int x)
{
	return !(x & 1);
	
	// Or 
	// return (x & 1) == 0;
}

// C function 2 to check for even numbers (Probably the most used method)
bool is_even_c_version2(int x)
{
	return (x % 2) == 0;
}

bool is_even_assembly(int x)
{
	bool result;

	asm volatile
	(
		"movl %1, %%eax\n" // Moves input's (x) value into the %eax register
		"andl $1, %%eax\n" // Bitwise AND operation with 1 to isolate least significant bit
		"cmpl $0, %%eax\n" // Change $1 to $0 to check for odd numbers
		"setne %%al\n" // Sets the low byte of %eax (%al) to 1 if not equal, otherwise 0
		"mov %%al, %0\n" // Moves the result in %al to output (result)
		:"=r"(result)
		:"r"(x)
		:"eax" // Clobbered register
	);

	return result;
}

int main(void)
{
	for (int i = 1; i <= 10; ++i)
	{
		if (is_even_assembly(i))
			printf("%d\n", i);
	}

	return 0;
}
