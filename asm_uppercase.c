#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void uppercase(char *str)
{
	asm volatile
	(
		"1:\n"
		"movb (%[str]), %%al\n"
		"testb %%al, %%al\n"
		"je 0f\n"
		"cmpb $97, %%al\n"
		"jl 2f\n"
		"cmpb $122, %%al\n"
		"jg 2f\n"
		"subb $32, %%al\n"
		"movb %%al, (%[str])\n"
		"2:\n"
		"inc %[str]\n"
		"jmp 1b\n"
		"0:"
		:
		:[str] "r"(str)
		:"al","memory"
	);
}

int main(void)
{
	char buf[512];

	FILE* fp = fopen("lorem.txt", "r");
	if (fp == NULL)
	{
		perror("fopen");
		return 1;
	}

	while (!feof(fp))
		fread(buf, sizeof(buf), 1, fp);

	fclose(fp);


	uppercase(buf);
	printf("%s\n", buf);


	return 0;
}
