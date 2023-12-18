#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[4];

	read(0, buf, 4);
	printf("%s", buf);
	return(33);
}