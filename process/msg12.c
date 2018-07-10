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
	int running = 1;
	struct Person person[5];
	int msgid,i;
	char buffer[BUFSIZ];

	msgid=msgget((key_t)1234,0666 | IPC_CREAT);

	if(msgid ==-1)
	{
		fprintf(stderr,"msgget failed with error: %d\n",errno);
		exit(EXIT_FAILURE);
	}

	//1. Generate data
	for(i=0;i<MAX_PERSON;i++)
	{
		person[i].my_msg_type = 1;
		sprintf(person[i].name,"lee%d",i);
		person[i].age = 20+i;
		person[i].id =i;
	}
/*	
	for(i=0;i<MAX_PERSON;i++)
	{
		printf("person[%d].my_msg_type: %ld\n",i,person[i].my_msg_type);
                printf("person[%d].name : %s\n",i,person[i].name);
	        printf("person[%d].age : %d \n",i,person[i].age);
	        printf("person[%d].id : %d \n",i,person[i].id);
	}
	*/
	//2. send data
	for(i=0;i<MAX_PERSON;i++)
	{
		if(msgsnd(msgid,(void*)&person[i],sizeof(person[i]),0)==-1)
		{
			fprintf(stderr,"msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}
	//for finishing msgque 
	person[0].my_msg_type = 3;
	 if(msgsnd(msgid,(void*)&person[0],sizeof(person[0]),0)==-1)
	 {
	              fprintf(stderr,"msgsnd failed\n");
	              exit(EXIT_FAILURE);
	 }

	if(person[0].my_msg_type==3)
	{
			running = 0;
	}
	
	exit(EXIT_SUCCESS);
}
