#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "bitmap.h"

int main()
{
	int res;
	void *shared_mem = (void*)0;
	BITMAPFILEHEADER fileHeader;    // 비트맵 파일 헤더 구조체 변수
	BITMAPINFOHEADER infoHeader; 
	
	int *image;
	int shmid;
	FILE *fpBmp;                    // 비트맵 파일 포인터
	
	int size;                // 픽셀 데이터 크기
	int width, height;       // 비트맵 이미지의 가로, 세로 크기
	int padding;             // 픽셀 데이터의 가로 크기가 4의 배수가 아닐 때 남는 공간의 크기
    
      
	fpBmp = fopen("lena.bmp", "rb");    // 비트맵 파일을 바이너리 모드로 열기

	if (fpBmp == NULL)    // 파일 열기에 실패하면
		return 0;         // 프로그램 종료
	 
	// 비트맵 파일 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
	{
		fclose(fpBmp);
	        return 0;
	}
		  // 매직 넘버가 MB가 맞는지 확인(2바이트 크기의 BM을 리틀 엔디언으로 읽었으므로 MB가 됨)
		  // 매직 넘버가 맞지 않으면 프로그램 종료
	if (fileHeader.bfType != 'MB')
	{
		fclose(fpBmp);
		return 0;
	}
			  
		// 비트맵 정보 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
	{
		fclose(fpBmp);
		return 0;
	}
	 
		// 24비트 비트맵이 아니면 프로그램 
	if (infoHeader.biBitCount != 24)
	{
		fclose(fpBmp);
		return 0;
	}
				       
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
	printf("Memory attached at %p\n",image);

	fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

	while(res!=0)
	{
		res = fread(image, size, 1, fpBmp);
		 res += res;
	}

	fclose(fpBmp);    // 비트맵 파일 닫기
 

	 if(shmdt(shared_mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	
	 exit(EXIT_SUCCESS);

}

