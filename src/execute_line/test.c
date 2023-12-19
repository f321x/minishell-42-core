#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd = open("testfile", O_RDONLY);
	char s[10];
	read(fd, s, 5);
	printf("%s\n", s);
}