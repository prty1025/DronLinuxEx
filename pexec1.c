#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("Running ps with eseclp\n");
	system("ps -ax");
	printf("Done.\n");
	exit(5);
}
