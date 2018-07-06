#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void pr_exit(int status);

int main(void)
{
	int status;
	pid_t pid;

	// 자신의 PID값을 확인한다.
	printf("Process ID = %d\n",getpid());

	// 부모의 PID값을 확인한다.
	printf("Parent Process ID = %d\n",getppid());

	//sleep(10); //cup가 다른프로세스를 진행시킴

	pid = fork();
	//부모에게 자식의 PID값을 알려줌 자식에게는 0의 값을 알려줌
	
	//fork()를 실행했는데 정상적으로 자식프로세스가 생성되지 않는 경우
	switch(pid)
	{
	case -1:
		printf("Error : fork()\n");
		exit(1);

	//자식 프로세스인 경우 실행
	case 0:
		printf("Child : Hello!!\n");
		raise(SIGINT);
		break;
		
	//부모 프로세스인 경우 실행
	default:
		printf("Parent : Hi!!\n");
		printf("Child PID : %d\n",pid);
		break;
	}

	pid = wait(&status);
	printf("EXIT : chaild pid = %d\n",pid);
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
