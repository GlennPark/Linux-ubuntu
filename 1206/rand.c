#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL)); //SEED VALUES PER CURRENT TIME
	printf("random variable : %d\n", rand());
	printf("random variable : %d\n", rand());
	printf("random variable : %d\n", rand());
    printf("random variable : %d\n", rand());
	printf("random variable : %d\n", rand());
    printf("random variable : %d\n", rand());
	return 0;


}
