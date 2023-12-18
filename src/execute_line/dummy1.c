#include <stdio.h>
#include <unistd.h>

int main()
{
	write(1, "test\n", 5);
	close(1);
	close(0);
	close(2);
}