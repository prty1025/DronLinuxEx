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
	int shmid, i;
	int *buffer;

	//srand((unsigned int)getpid());
	shmid = shmget((key_t)1234,sizeof(int)*TEXT_SZ,0666 | IPC_CREAT);
	
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
	buffer = (int*)shared_memory;
	//shared_stuff->written_by_you = 0;
	while(running)
	{
		for(i=0;i<TEXT_SZ;i++)
		{

			printf("You wrote: %d\n",*(buffer+i));
	
		}
		running = 0;
	}
		
	
	if(shmdt(shared_memory)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}
