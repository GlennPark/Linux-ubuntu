#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <limits.h>                     /* USHRT_MAX 상수를 위해서 사용한다. */
#include <math.h>

#include <unistd.h>

#include "bmpHeader.h"

/* 이미지 데이터의 경계 검사를 위한 매크로 */
#define LIMIT_UBYTE(n) ((n)>UCHAR_MAX)?UCHAR_MAX:((n)<0)?0:(n)

typedef unsigned char ubyte;

void userqsort(int a[], int n)
{
	int i, j;
	for(i = 1; i < n; i++){
		int tmp = a[i];
		for(j = i; j > 0 && a[j - 1] > tmp; j --)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
	
}



int main(int argc, char** argv) 
{
    FILE* fp; 
    BITMAPFILEHEADER bmpHeader;             /* BMP FILE INFO */
    BITMAPINFOHEADER bmpInfoHeader;     /* BMP IMAGE INFO */
    RGBQUAD *palrgb;
    ubyte *inimg, *padimg, *outimg, *grayimg, gray;
    int x, y, z, imageSize, graySize;

	float b, g, r;
    if(argc != 3) {
        fprintf(stderr, "usage : %s input.bmp output.bmp\n", argv[0]);
        return -1;
    }
    
    /***** read bmp *****/ 
    if((fp=fopen(argv[1], "rb")) == NULL) { 
        fprintf(stderr, "Error : Failed to open file...\n"); 
        return -1;
    }

    /* BITMAPFILEHEADER 구조체의 데이터 */
    fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

    /* BITMAPINFOHEADER 구조체의 데이터 */
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    /* 트루 컬러를 지원하면 변환할 수 없다. */
    if(bmpInfoHeader.biBitCount != 24) {
        perror("This image file doesn't supports 24bit color\n");
        fclose(fp);
        return -1;
    }
    
    int elemSize = bmpInfoHeader.biBitCount/8;
    int size = bmpInfoHeader.biWidth*elemSize;
    imageSize = size * bmpInfoHeader.biHeight; 
//    graySize = (sizeof(ubyte)bmpInfoHeader.biWidth * bmpInfoHeader.biHeight));
    /* 이미지의 해상도(넓이 × 깊이) */
    printf("Resolution : %d x %d\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    printf("Bit Count : %d\n", bmpInfoHeader.biBitCount);     /* 픽셀당 비트 수(색상) */
    printf("Image Size : %d\n", imageSize);

    inimg = (ubyte*)malloc(sizeof(ubyte)*imageSize); 
    outimg = (ubyte*)malloc(sizeof(ubyte)*imageSize);
    grayimg = (ubyte*)malloc(sizeof(ubyte)*imageSize); 

	fread(inimg, sizeof(ubyte), imageSize, fp); 
    fclose(fp);

//white noise add
/*    srand((unsigned int)time(NULL));
    cnt = atoi(argv[1]);
    for(i = 0; i < cnt; i++){
        int pos  = rand()%(bmpInfoHeader.biHeight * bmpInfoHeader.biWidth);
        int val = rand()&ob11111111;
        for(z=0; z < elemSize; z++){
            int tmp = inimg[pos*elemSize+z] + value;
            inimg[pos*elemSize+z] = LIMIT_UBYTE(p);
 
        }
    }
*/

for(y = 0; y < bmpInfoHeader.biHeight; y++){
	for(x = 0; x < bmpInfoHeader.biWidth; x++){
	b = (float)inimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 0];
	g = (float)inimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 1];
	r = (float)inimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 2];

	gray = (r*0.299F)+(g*0.587F)+(b*0.114F);
	grayimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 0]=gray;
	grayimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 1]=gray;
	grayimg[3*x + (y*bmpInfoHeader.biWidth)*3 + 2]=gray;
	}
}

	int padSize = (bmpInfoHeader.biWidth + 2) * elemSize;
    int addSize = (padSize + bmpInfoHeader.biHeight)*2;
    padimg = (ubyte*)malloc(sizeof(ubyte)*(imageSize + addSize));

    /* make padding image */
    memset(padimg, 0, (sizeof(ubyte)*(imageSize + addSize)));
    //memset(outimg, 0, sizeof(ubyte)*imageSize);
    for(y = 0; y < bmpInfoHeader.biHeight; y++) {
        for(x = 0; x < bmpInfoHeader.biWidth * elemSize; x+=elemSize) {
            for(z = 0; z < elemSize; z++) {
                padimg[(x+elemSize)+(y+1)*padSize+z]=grayimg[x+y*size+z];
            }
        }
    }

    for(y = 0; y < bmpInfoHeader.biHeight; y++) { 
        for(z = 0; z < elemSize; z++) {
            padimg[0+(y+1)*padSize+z]=grayimg[0+y*size+z];
            padimg[padSize-elemSize+(y+1)*padSize+z]=grayimg[size-elemSize+y*size+z];
        }
    }

    for(x = 0; x < bmpInfoHeader.biWidth*elemSize; x++) { 
        padimg[elemSize+x]=grayimg[x];
        padimg[elemSize+x+(bmpInfoHeader.biHeight+1)*padSize]=grayimg[x+(bmpInfoHeader.biHeight-1)*size];

    }

    for(z = 0; z < elemSize; z++) {
       padimg[z]=grayimg[z];
       padimg[padSize-elemSize+z]=grayimg[size-elemSize+z];
       padimg[(bmpInfoHeader.biHeight+1)*padSize+z]=grayimg[(bmpInfoHeader.biHeight-1)*size+z];
       padimg[(bmpInfoHeader.biHeight+1)*padSize+padSize-elemSize+z]=grayimg[(bmpInfoHeader.biHeight-1)*size+size-elemSize+z];
    }

    // define the kernel
    float kernelx[3][3] = { {-1, 0, 1},
                            {-2, 0, 2},
                            {-1, 0, 1} };
	
	float kernely[3][3] = { {1, 2, 1},
                            {0, 0, 0},
                            {-1, -2, -1} };



int arr[9];
int tmp;
//int count;

    memset(outimg, 0, sizeof(ubyte)*imageSize);
    for(y = 1; y < bmpInfoHeader.biHeight + 1; y++) { 
        for(x = elemSize; x < padSize; x+=elemSize) {
            for(z = 0; z < elemSize; z++) {
                float xtox = 0.0, ytoy = 0.0;
		//		count = 0;
				for(int i = -1; i < 2; i++) {
                    for(int j = -1; j < 2; j++) {
					
                  xtox += kernelx[x+1][y+1]
					  *padimg[(x+i*elemSize)+(y+j)*padSize+z];				 
				  ytoy += kernely[x+1][y+1]
					  *padimg[(x+i*elemSize)+(y+j)*padSize+z];  
					}
                }
                outimg[(x-3)+(y-1)*3*bmpInfoHeader.biWidth+z] = LIMIT_UBYTE(sqrt(xtox*xtox + ytoy*ytoy)); 
            }
        }
    }         
	
	
	/***** write bmp *****/ 
    if((fp=fopen(argv[2], "wb"))==NULL) { 
        fprintf(stderr, "Error : Failed to open file...₩n"); 
        return -1;
    }

    /* BITMAPFILEHEADER 구조체의 데이터 */
    fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);

    /* BITMAPINFOHEADER 구조체의 데이터 */
    fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    //fwrite(inimg, sizeof(ubyte), imageSize, fp); 
    //fwrite(padimg, sizeof(ubyte), imageSize, fp);
    fwrite(outimg, sizeof(ubyte), imageSize, fp);

    fclose(fp); 

    free(inimg); 
    free(outimg);
    free(padimg);
    
    return 0;
}
