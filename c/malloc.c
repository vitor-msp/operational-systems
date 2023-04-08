#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    int counter = 0;
    while (1)
    {
        if (counter % 1024 == 0)
        {
            int *ptr = (int *)malloc(10 * sizeof(int));
            printf("%p\n", ptr);
        }
        counter++;
    }
}