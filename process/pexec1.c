#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("Running ps with system\n");
	system("ps -ax");
	printf("Done.\n");
	exit(5);
}
