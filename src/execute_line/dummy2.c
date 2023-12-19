#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[10];

	int r = read(0, buf, 7);
	printf("|%s|", buf);
	printf("%d\n", r);
	return(33);
}