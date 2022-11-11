#include <stdio.h>
#include <stdlib.h>
int global_data = 1;
const int text_seg[1000] = {0};
main()
 {
    int i;
    void *p = malloc(128);
    printf("The stack top is near %p\n", &i);
    printf("The location of global_data in the initialized data segment is %p\n", &global_data);
    printf("The location of text_seg in the text segment is %p\n", &text_seg);
    printf("The location of p in the heap segment is %p\n", p);
    return 0;
}
