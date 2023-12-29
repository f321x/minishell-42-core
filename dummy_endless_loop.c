#include <stdio.h>
#include <unistd.h>

int main()
{
	char	buffer[10];

	write(1, "prompt>", 7);
	while (1)
		read(1, buffer, 10);
}