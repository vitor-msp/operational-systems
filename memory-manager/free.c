#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define TIME 10

int run_malloc = 1;

void malloc_alarm(int)
{
    run_malloc = 0;
}

void main(void)
{
    char *ptr, *first_ptr;
    int first_element = 1, counter = 0, i = 0;
    signal(SIGALRM, malloc_alarm);
    alarm(TIME);
    while (run_malloc)
    {
        ptr = (char *)malloc(1);
        if (first_element)
        {
            first_ptr = ptr;
            first_element = 0;
        }
        printf("%p\n", ptr);
        counter++;
    }
    printf("==== end of malloc ==== \n");
    free(first_ptr);
    printf("%p\n", first_ptr);
    first_ptr += 48 + 2048;
    while (i < counter - 1)
    {
        ptr = first_ptr + 2048 + 32 * i++;
        printf("%p\n", ptr);
        free(ptr);
    }
}