#include <stdio.h>
#include <stdint.h>

int32_t gen_rand_num(int32_t min, int32_t max)
{
	int32_t rand;
	if (min >= 0 && max <= INT32_MAX)
	{
		asm volatile
		(
			"rdtsc\n" // rdtsc produces a "timestamp counter" and stores the lower 32 bits in %eax and the higher 32 bits in %edx
			"movl %%eax, %%ebx\n" // We move the lower 32 bits into EBX
			"xorl %%edx, %%edx\n" // Reset EDX 
			"movl %[max], %%ecx\n" // Max requested value is stored in ECX
			"divl %%ecx\n" // EBX is divided by the value stored in ECX, the remainder is stored in EDX
			"addl %[min], %%edx\n" // We add the Min requested value to EDX
			"movl %%edx, %0\n" // EDX now contains the reminder + the Min requested value. int num = rand() % MAX + MIN;
			: "=r"(rand)
			: [min] "r" (min), [max] "r" (max)
			: "eax","ecx","edx","ebx"
		);
	}

	return rand;
}

int main(void)
{
	int i = 1;
	while(i++ <= 100)
	{	
		printf("%d\n", gen_rand_num(1, 100));
	}

	return 0;
}
