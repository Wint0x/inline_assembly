#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rev_str(char *str)
{
	unsigned int len = strlen(str);

	char *temp = (char*)malloc(len);
	if (temp == NULL)
	{
		perror("malloc");

		exit(1);
	}

	asm volatile
	(
		"movl $0, %%ecx\n" 
		"movl %[len], %%ebx\n"
		"dec %%ebx\n"
		"0:\n"
		"inc %[src]\n"
		"inc %%ecx\n"
		"cmpl %%ebx, %%ecx\n"
		"jl 0b\n"
		"nop\n"
		"1:\n"
		"movb (%[src]), %%al\n"
		"movb %%al, (%[dst])\n"
		"inc %[dst]\n"
		"dec %[src]\n"
		"dec %%ecx\n"
		"cmpl $0, %%ecx\n"
		"jge 1b\n"
		:
		:[src] "r" (str), [dst]"r"(temp), [len] "r" (len)
		:"al","ebx","ecx","memory"
	);

	temp[len] = '\0';
	strcpy(str, temp);

	free(temp);
}

int main(void)
{
	char str[] = "hello world";

	rev_str(str);
	printf("%s\n", str); // dlrow olleh

	return 0;
}
