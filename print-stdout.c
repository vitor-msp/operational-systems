#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define SIZE 8

void main()
{
    char msg[SIZE] = {'B', 'o', 'm', ' ', 'd', 'i', 'a', '\n'};
    write(1, &msg[0], SIZE);
    write(2, &msg[0], SIZE);
    return;
}