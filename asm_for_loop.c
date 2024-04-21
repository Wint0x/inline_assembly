#include <stdio.h>

int main(void)
{	
	int sum;

	// ASM for loop
	asm volatile
	(
		"movl $0, %0\n" // Move 0 into sum
		"movl $1, %%ecx\n" // Move 1 into the ecx register (this will represent our current iteration counter)
		"jmp 2f\n" // Jump-forward to label 2
		"1:\n"
		"addl %%ecx, %0\n" // Add the current value in ecx to sum
		"addl $1, %%ecx\n" // Increment ecx's value by 1
		"2:\n"
		"cmpl $10, %%ecx\n" // Compares "10" to the current iteration's value
		"jle 1b\n" // Jump-back to label 1 if ecx is less than 10 
		:"=r"(sum)
		:
		:"ecx" // Clobbered register
	);

	printf("%d\n", sum); // Output: 55

	return 0;
}
