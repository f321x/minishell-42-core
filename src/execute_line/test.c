#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char *a = malloc(-1);
	perror("mytest");
	printf("-%p", a);
}