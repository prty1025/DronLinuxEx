#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mem_size 200

int a=10;
int b=0;
int arry[10];
int const img[5]={0,1,2,3,4};
char *pData="Hello World";

void main(void)
{

	static int c;
	static int d = 15;
	char label[100];
	char* pLabel;
		
	pLabel = malloc(sizeof(char)*mem_size);
	
	printf("pLabel addr : %p\n",&pLabel);
	printf("pData addr : %p\n",&pData);
	printf("a addr : %p\n",&a);
	printf("b addr : %p\n",&b);
	printf("c addr : %p\n",&c);
	printf("d addr : %p\n",&d);
	printf("label addr : %p\n",label);
	printf("arry addr : %p\n",arry);
	printf("img addr : %p\n",img);



	//printf("pLabel addr : %p\n",&pLabel);

	
	free(pLabel);
}


