#include "util.h"

void _start(void)
{	
	char buf[32];
	print("Enter text: ");

	read(0, buf, sizeof(buf));

	write(1, buf, strlen(buf));

	sysexit(12);
}
