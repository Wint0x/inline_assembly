#include <stdio.h>

/* Mathematical functions that use Assembly */
long square(long num)
{
	long result;

	asm volatile
	(
		"movq %1, %%rax\n" 		// Move input into %rax register
		"imulq %%rax, %%rax\n" // Mult value in %rax by itself
		"movq %%rax, %0\n" 	  // Move value in %rax to the output
		:"=r" (result) 		 // Output
		:"r" (num) 			// Input
		:"%rax" 		   // Clobbered register
	);

	return result;
}

double sum_doubles(double n1, double n2)
{
	double result;
	asm volatile
	(
		"addsd %[n1], %[n2]\n"           // Adds n1 to n2 as doubles
		"movsd %[n2], %[result]\n"      // Moves n2 to result (output variable)
		:[result] "=x" (result)        // Output: result in xmm register
		:[n1] "x" (n1), [n2] "x" (n2) // Input: n1 and n2 in xmm registers
		: 				 			 // No clobbered registers
	);

	return result;
}

int main(void)
{
	long x = square(12); // 144
	double y = sum_doubles(1.25, 3.25); // 4.500000

	printf("%d ^ 2 = %ld\n", 12, x);
	printf("%lf + %lf = %lf\n", 1.25, 3.25, y);

	return 0;
}
