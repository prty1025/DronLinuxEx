#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "data.h"


int main()
{
	int i;
	int running =1;
	int msgid;
	struct Person person[MAX_PERSON];

	
	long int msg_to_receive = 0;
	msgid = msgget((key_t)1234,0666 | IPC_CREAT);

	if(msgid ==-1)
	{
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<MAX_PERSON;i++)
	{
		if(msgrcv(msgid,(void*)&person[i],BUFSIZ,msg_to_receive,0) == -1)
		{
			fprintf(stderr,"msgtcv failed with error: %d\n",errno);
			exit(EXIT_FAILURE);
		}
		if(person[i].my_msg_type!=3)
		{
			printf("name : %s\n",person[i].name);
			printf("age: %d\n",person[i].age);
			printf("id: %d\n",person[i].id);

		}
		else if(person[i].my_msg_type ==3)
			break;
	}
	
	if(msgrcv(msgid,(void*)&person[i],BUFSIZ,msg_to_receive,0) == -1)
	{
	           fprintf(stderr,"msgtcv failed with error: %d\n",errno);
	           exit(EXIT_FAILURE);        
	}

	if(person[0].my_msg_type==3)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	if(msgctl(msgid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
