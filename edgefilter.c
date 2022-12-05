#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//for(i = 0; i < 256; i++) histogram[i] = 0;


#define BYTE	unsigned char
#define BASE    16

int main(int argc, char **argv)
{
fread(&type, sizeof(unsigned short int), 1, fp);
	fread(&file_size, sizeof(unsigned int), 1, fp);
	fread(&reserved1, sizeof(unsigned short int), 1, fp);
	fread(&reserved2, sizeof(unsigned short int), 1, fp);
	fread(&offset, sizeof(unsigned int), 1, fp);
	fread(&header_size, sizeof(unsigned int), 1, fp);
	fread(&width, sizeof(int), 1, fp);
	fread(&height, sizeof(int), 1, fp);
	fread(&planes, sizeof(unsigned short int), 1, fp);
	fread(&bits, sizeof(unsigned short int), 1, fp);
	fread(&compression, sizeof(unsigned int), 1, fp);
	fread(&imagesize, sizeof(unsigned int), 1, fp);
	fread(&hresolution, sizeof(int), 1, fp);
	fread(&vresolution, sizeof(int), 1, fp);
	fread(&ncolors, sizeof(unsigned int), 1, fp);
	fread(&importantcolors, sizeof(unsigned int), 1, fp);

	size = widthbytes(bits * width);
		if(!imagesize) imagesize = height * size;
	inimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);
	outimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);
	fread(inimg, sizeof(BYTE), imagesize, fp);
	fclose(fp);
	for(i = 0; i < height; i++) {
		index = (height-i-1) * size; 
		for(j = 0 ; j < width; j++) { 
			r = (float)inimg[index+3*j+2];
			g = (float)inimg[index+3*j+1];
			b = (float)inimg[index+3*j+0];
			gray1 = (r*0.3F)+(g*0.59F)+(b*0.11F);
		
            r = (float)inimg[index+3*j+2-3];
            g = (float)inimg[index+3*j+1-3];
            b = (float)inimg[index+3*j+0-3];
            gray1 = (r*0.3F)+(g*0.59F)+(b*0.11F);
           
			value = (int)(gray2 - gray1);
			outimg[index + 3*j] = (value > BASE)? 255:0;
			outimg[index + 3*j +1] = (value > BASE)? 255:0;
			outimg[index + 3*j +2] = (value > BASE)? 255:0;

			r = (float)inimg[index+3*j+2];
            g = (float)inimg[index+3*j+1];
            b = (float)inimg[index+3*j+0];
            gray1 = (r*0.3F)+(g*0.59F)+(b*0.11F);
}




//		};
//	};
