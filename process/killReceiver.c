#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sigHandler(int sig)
{
	static int count =0;
	
	printf("OUCH! - I got SIGINT %d\n",sig);
	count ++;
	if(count==5)
		exit(0);

//	(void) signal(SIGINT,SIG_DFL);


}

int main()
{
	signal(SIGINT,sigHandler);
	

	while(1)
	{
		printf("Hello world!\n");
		sleep(1);
	}
}

