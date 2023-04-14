#include <stdlib.h>
#include <stdio.h>

void main(void)
{
    int var[] = {100, 101};
    int *ptr = &var[0];
    printf("%p\n", ptr + 32 * 0);
    printf("%p\n", ptr + 32 * 1);
    printf("%p\n", ptr + 32 * 2);
}