#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[10];

	int r = read(0, buf, 10);
	write(1, "|", 1);
	write(1, buf, r);
	write(1, "|", 1);
	r = read(0, buf, 10);
	exit(33);
}