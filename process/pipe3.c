#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
	int data_processed;
	int file_pipes[2];
	int status;
	int fd;
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	pid_t fork_result;
	memset(buffer,'\0',sizeof(buffer));

	fd =open("./test.txt",O_RDONLY,0666);
	if(pipe(file_pipes)==0)
	{
		fork_result=fork();
		if(fork_result==-1)
		{
			fprintf(stderr,"Fork failure");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0)
		{
		data_processed=read(fd,buffer,10);
		buffer[data_processed]='\0';
		printf("Child : %s\n",buffer);
			sprintf(buffer,"%d",file_pipes[0]);
			execl("pipe4","pipe4",buffer,(char*)0);
			exit(EXIT_FAILURE);
		}
		else
		{
			 data_processed=read(fd,buffer,10);
			 buffer[data_processed]='\0';
			 printf("Parents : %s\n",buffer);

			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("%d - wrote %d bytes\n",getpid(),data_processed);
		}
	}
	
	wait(&status);

	close(file_pipes[0]);
	close(file_pipes[1]);
	exit(EXIT_SUCCESS);
}

