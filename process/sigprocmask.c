#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_quit(int);

int main(void)
{
	sigset_t newmask,oldmask, pendmask;

	if(signal(SIGQUIT,sig_quit)==SIG_ERR)
		perror("can't catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
		perror("SIG_BLOCK error");

	sleep(5);
	if(sigpending(&pendmask)<0)
		perror("sigpending error");
	if(sigismember(&pendmask,SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
		perror("SIG_SETMASK error");
	printf("SIGQUIT unblocked\n");

	sleep(5);
	exit(0);
}
static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
		perror("can't reset SIGQUIT");
}

