#include <stdio.h>

int main(int argc, char *argv)
{
    struct point {
	int x;
	int y;
    };

    struct point p = { 1.0, 2.0 };

    printf("p.x = %d\n", p.x);
    printf("p.y = %d\n", p.y);
}

