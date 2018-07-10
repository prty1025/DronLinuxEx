#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st
{
	long int my_msg_type;
	char some_text[MAX_TEXT];
};

int main()
{
	int running = 1;
	struct my_msg_st some_data;
	int msgid;
	char buffer[4];
	char buffer1[BUFSIZ];
	

	msgid=msgget((key_t)1234,0666 | IPC_CREAT);

	if(msgid ==-1)
	{
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("enter msg_type: ");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type = atoi(buffer);
		
		printf("enter some text: ");
		fgets(buffer1,BUFSIZ,stdin);
		
		strcpy(some_data.some_text,buffer1);

		if(msgsnd(msgid,(void*)&some_data,MAX_TEXT,0)==-1)
		{
			fprintf(stderr,"msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		if(some_data.my_msg_type==3)
		{
			running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}
