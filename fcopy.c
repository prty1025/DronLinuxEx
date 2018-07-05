#include <stdio.h>


int main(int argc, char **argv)
{
	int count;
	FILE *in, *out;
	char buf[BUFSIZ]; //8192로 선언되어있음 


       //printf("BUFSIZ=%d\n",BUFSIZ);

	if(argc<3)
	{
		fprintf(stderr,"Usage : file1 file2\n");
		return -1;
	}

	if((in =fopen(argv[1],"r"))==NULL)
	{
		perror(argv[1]);
		return -1;
	}
	if((out = fopen(argv[2],"w"))==NULL)
	{
		perror(argv[2]);
		return -1;
	}

	//원본파일의 내용을 읽어서 대상파일에 쓰기
	while((count = fread(buf,sizeof(char),BUFSIZ,in))>0)
		fwrite(buf,sizeof(char),count,out);
	
	fclose(out);
	fclose(in);
	
	return 0;

}
