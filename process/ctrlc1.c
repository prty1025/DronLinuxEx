#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sigHandler(int sig)
{
	static int count =0;
	switch(sig)
	{
	case SIGINT:
		printf("OUCH! - I got SIGINT %d\n",sig);
		count ++;
		if(count==5)
			exit(0);
		break;
	case SIGQUIT:
		printf("OUCH! - I got SIGQUIT %d\n",sig);
		break;
	default:
		break;
		
	}

	//(void) signal(SIGINT,SIG_DFL);
	(void) signal(SIGQUIT,SIG_DFL);

}

int main()
{
	signal(SIGINT,sigHandler);
	signal(SIGQUIT,sigHandler);

	while(1)
	{
		printf("Hello world!\n");
		sleep(1);
	}
}

