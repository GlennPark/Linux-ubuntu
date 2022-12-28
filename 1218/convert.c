#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bmpHeader.h>

#define widthBytes(bits) (((bits)+31)/32*4)
#define LIMIT_UBYTE(n) ((n)>UCHAR_MAX)?UCHAR_MAX:((n)<0)?0:(n)

int main()
{
	


}

