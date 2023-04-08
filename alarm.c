#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;

void alarm_action(int par)
{
    printf("test\n");
    exit(0);
}

void main()
{
    signal(SIGALRM, alarm_action);
    alarm(10);
    alarm(10);
    pause();
}