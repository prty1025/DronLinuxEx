#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 20000
int main()
{
	FILE *read_fp;
	char buffer[BUFSIZE+1];
	int chars_read;

	memset(buffer,'\0',sizeof(buffer));
	read_fp=popen("ps -ax","r");

	if(read_fp != NULL)
	{
		chars_read =fread(buffer,sizeof(char),BUFSIZE,read_fp);
		while(chars_read>0)
		{
			buffer[chars_read]='\0';
			printf("Reading:-\n %s\n",buffer);
			chars_read = fread(buffer,sizeof(char),BUFSIZE,read_fp);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
