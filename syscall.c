#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	int p1,p2;

	p1 = syscall(__NR_getpid);
	p2 = getpid();

	printf("syscall: %d\n",p1);
	printf("getpid: %d\n",p2);
	return 0;
}

