#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 0, count = (int)sizeof(&argv);
    printf("argc %d\n", argc);
    printf("argv %d\n", count);
    while (i < count)
    {
        printf("argv %s\n", argv[i]);
        i++;
    }
    return 0;
}