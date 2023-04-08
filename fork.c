#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int statloc, pid = fork();
    if (pid < 0)
    {
        return 1;
    }
    else if (pid > 0)
    {
        pid = waitpid(pid, &statloc, 0);
        printf("pai: %d, filho: %d, filho_status: %d\n", getpid(), pid, statloc);
    }
    else
    {
        printf("filho: %d\n", getpid());
        exit(2);
    }
    return 0;
}
