#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int s, sig,i;
	if(argc != 3||strcmp(argv[1],"--help")==0)
	printf("%s pid sig-num\n",argv[0]);
	sig =atoi(argv[2]);
	printf("argv[1]=%d\n",sig);
	
	for(i=0;i<5;i++)
	{
		s= kill(atoi(argv[1]),sig);
		sleep(1);

	if(sig!=0)
	{
		if(s==-1)
			printf("Error : system call kill()\n");
	
		else if(s==0)
			printf("Process exists and we can send it a signal\n");
	}
	}
	return 0;


}
