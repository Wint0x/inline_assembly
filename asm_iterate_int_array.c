#include <stdio.h>

static inline void inc_arr(int *arr, const int size)
{
	asm volatile
	(
		"lea (%[array]), %%rdi\n"
		"movl %[array_size], %%ebx\n"
		"movl $1, %%ecx\n"
		"1:\n"
		"addl $1, (%%rdi)\n"
		"add $4, %%rdi\n"
		"inc %%ecx\n"
		"cmpl %%ebx, %%ecx\n"
		"jle 1b"
		:
		:[array] "r" (arr), [array_size] "r" (size)
		:"rdi","ebx","ecx","memory"
	);
}

int main(void)
{
	const int size = 5;
	int arr[] = {1,2,3,4,5};

	inc_arr(arr, size);

	for (int i = 0; i < size; ++i)
		printf("%d\n", arr[i]);

	return 0;
}
