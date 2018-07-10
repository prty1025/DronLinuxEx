#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bitmap.h"

int main()
{
	int x,y;
	void *shared_mem = (void*)0;
	BITMAPFILEHEADER fileHeader;    // 비트맵 파일 헤더 구조체 변수
	BITMAPINFOHEADER infoHeader; 
	
	int *image;
	int shmid;
	FILE *fpTxt;                    // 비트맵 파일 포인터
	
	int size;                // 픽셀 데이터 크기
	int width, height;       // 비트맵 이미지의 가로, 세로 크기
	int padding;             // 픽셀 데이터의 가로 크기가 4의 배수가 아닐 때 남는 공간의 크기
    
	char ascii[] = { '#', '#', '@', '%', '=', '+', '*', ':', '-', '.', ' ' };
	 
	 
				       
	size = infoHeader.biSizeImage;    // 픽셀 데이터 크기
	width = infoHeader.biWidth;       // 비트맵 이미지의 가로 크기
	height = infoHeader.biHeight;     // 비트맵 이미지의 세로 크기
					    
	padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;
	 if (size == 0)    // 픽셀 데이터 크기가 0이라면
	 {
	       size = (width * PIXEL_SIZE + padding) * height;
	 }
	

	shmid =shmget((key_t)1234, size,0666 | IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_mem =shmat(shmid,(void*)0,0);
	if(shared_mem ==(void*)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}

	image = (int*)shared_mem;

	fpTxt = fopen("ascii.txt", "w"); 
	printf("Memory attached at %p\n",image);

	if (fpTxt == NULL)    // 파일 열기에 실패하면
		return 0;         // 프로그램 종료

	for (int y = height - 1; y >= 0; y--)
	{
		// 가로 크기만큼 반복
		for (int x = 0; x < width; x++)
	        {
			int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);
			RGBTRIPLE *pixel = (RGBTRIPLE *)&image[index];
			unsigned char blue = pixel->rgbtBlue;
			unsigned char green = pixel->rgbtGreen;
			unsigned char red = pixel->rgbtRed;
			unsigned char gray = (red + green + blue) / PIXEL_SIZE;
			char c = ascii[gray * sizeof(ascii) / 256];

			fprintf(fpTxt, "%c%c", c, c);    // 텍스트 파일에 문자 출력
		}

		fprintf(fpTxt, "\n");    // 가로 픽셀 저장이 끝났으면 줄바꿈을 해줌
	}

	
	fclose(fpTxt);    

	 if(shmdt(shared_mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl failed\n");
		exit(EXIT_FAILURE);
	}
	
	 exit(EXIT_SUCCESS);

}

