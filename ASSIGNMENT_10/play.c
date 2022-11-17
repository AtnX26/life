#include <stdio.h>
char ga[4] ={'A','B','C', '\0'}; 

void one(char ca[])
{
	printf("%p\n", &ca);
	printf("%p\n", &(ca[0]));
	printf("%p\n", &(ca[1]));
}

void two(char *pa)
{
	printf("%p\n", &pa);
	printf("%p\n", &(pa[0]));
	printf("%p\n", &(pa[1]));
	printf("%p\n", ++pa);
}

int main()
{
	char ca[4];
	char *pa;
	one (ca);
	two (pa);
	one(ga);
	two(ga);
	printf("Value of &ga: %p\n", &ga);
	printf("Value of &(ga[0]): %p\n", &(ga[0]));
	printf("Value of &(ga[1]): %p\n", &(ga[1]));
}

