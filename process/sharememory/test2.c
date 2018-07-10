#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define TEXT_SZ 100

int main()
{
	int running = 1;
	void *shared_memory =(void*)0;
	//struct shared_use_st *shared_stuff;
	int shmid;
	int i;
	int *buffer;
	//int buffer[100];
	
	

	shmid = shmget((key_t)1234,sizeof(int)*TEXT_SZ, 0666 | IPC_CREAT);
	
	if(shmid == -1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	shared_memory = shmat(shmid,(void*)0,0);
	if(shared_memory ==(void*)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %p\n",(int*)shared_memory);
	buffer  = (int*)shared_memory;
	//shared_stuff->written_by_you = 0;
	while(running)
	{
		for(i=0;i<TEXT_SZ;i++)
		{
			*(buffer+i)=i;
			printf("%d\n",*(buffer+i));
		}
		running=0;

		
	}
	if(shmdt(shared_memory)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}
