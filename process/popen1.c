#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *read_fd;
	char buffer[BUFSIZ+1];
	int chars_read;
	memset(buffer,'\0',sizeof(buffer));
	read_fd = popen("uname -a","r");
	if(read_fd != NULL)
	{
		chars_read = fread(buffer,sizeof(char),BUFSIZ,read_fd);
		if(chars_read>0)
		{
			printf("Output was:-\n%s\n",buffer);
		}
		pclose(read_fd);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
