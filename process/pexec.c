#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void pr_exit(int status);

int main()
{
  int status;
  pid_t pid;

  pid = fork();

  if(pid < 0)
  {
   	printf("errer!!\n");
   	return -1;
  }
  else if(pid == 0)
  {
   	printf("child\n");
	execlp("./pexec1","pexec1",(char*) 0);
	exit(5);
	return -1;
  }
   else

   	printf("child PID : %d\n",pid);
	wait(&status);
	pr_exit(status);
	return 0;

}
void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),WCOREDUMP(status) ? "core file generated)" : "");
	else if(WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",WSTOPSIG(status));
}
