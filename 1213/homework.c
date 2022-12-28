#include "bmpHeader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(*argc, **argv)
{
	
	FILE *file

	BITMAPFILEHEADER bmpFHeader;
	BITMAPINFOHEADER bmpIHeader;

	file = fopen(filename, "rb");
	if(file == NULL){
		perror("ERR\n");

		return -1
	}
	
	int Mask= 0b0;
	for(x = 0; x < bmpIHeader.biBitCount; x++)
	{
		Mask |= 
	}

	fread(&bmpFHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&bmpIHeader, sizeof(BITMAPINFOHEADER), 1, file);
	
	if(bmpIHeader.biBitCount != 24)
	{
		perror("This File is not 24 bit\n");
		fclose(file);
		return -1;
	}

	


	fwrite(&bmpFHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fwrite(&bmpFHeader, sizeof(BITMAPFILEHEADER), 1, file);




	fclose(file);

	return 0;

}

