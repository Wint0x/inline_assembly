#include <stdio.h>
#include <stdlib.h>

void cube(unsigned *num)
{
	unsigned times = *num;

	asm volatile
	(
		"movl (%0), %%eax\n"
		"mov $1, %%ecx\n" // iteration counter
		"1:\n"
		"inc %%ecx\n"
		"imul %[power], %%eax\n"
		"cmpl $3, %%ecx\n" // compare with 3
		"jne 1b\n" // jump back to 1: if not equal
		"movl %%eax, (%0)"
		:
		:"r"(num), [power] "r" (times)
		:"eax","ecx","memory"
	);
}

int main(void)
{
	FILE* fp = freopen("test.txt", "a", stdout);
	if (fp == NULL)
	{
		perror("freopen");
		return 1;
	}

	unsigned temp;
	for (int i = 1; i <= 100; ++i)
	{
		temp = i;
		cube(&temp);

		printf("%d ^ 3 = %d\n", i, temp);
	}

	fclose(fp);
	return 0;
}
