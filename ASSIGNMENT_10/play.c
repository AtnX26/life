#include <stdio.h>
char ga[4] ={'A','B','C', '\0'}; 

void one(char ca[])
{
	printf("Value of &ca: %p\n", &ca);
	printf("Value of &(ca[0]): %p\n", &(ca[0]));
	printf("Value of &(ca[1]): %p\n", &(ca[1]));
}

void two(char *pa)
{
	printf("Value of &pa: %p\n", &pa);
	printf("Value of &(pa[0]): %p\n", &(pa[0]));
	printf("Value of &(pa[1]): %p\n", &(pa[1]));
	printf("Value of ++pa: %p\n", ++pa);
}

int main()
{
	char ca[4];
	char *pa;
	one(ga);
	two(ga);
	printf("Value of &ga: %p\n", &ga);
	printf("Value of &(ga[0]): %p\n", &(ga[0]));
	printf("Value of &(ga[1]): %p\n", &(ga[1]));
}

