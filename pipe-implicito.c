#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ (fd[0])
#define WRITE (fd[1])
#define FILHO1 (pid1 == 0)
#define PAI1 (pid1 > 0)
#define FILHO2 (pid2 == 0)
#define PAI2 (pid2 > 0)

int main(int argc, char *argv[])
{
    char *file1 = argv[1], *file2 = argv[2];
    int fd[2], pid1, pid2, statloc1, statloc2;
    pipe(fd);
    pid1 = fork();
    if (FILHO1)
    {
        printf("filho 1 %d\n", getpid());
        close(READ);
        dup2(WRITE, 1);
        close(WRITE);
        execlp(file1, file1, (char *)0);
    }
    if (PAI1)
    {
        printf("pai: acabei de criar o filho 1 -> pid %d\n", pid1);
        close(WRITE);
        pid2 = fork();
        if (FILHO2)
        {
            printf("filho 2 %d\n", getpid());
            dup2(READ, 0);
            close(READ);
            execlp(file2, file2, (char *)0);
        }
        if (PAI2)
        {
            printf("pai: acabei de criar o filho 2 -> pid %d\n", pid2);
            close(READ);
            waitpid(pid1, &statloc1, 0);
            waitpid(pid2, &statloc2, 0);
            printf("pai acordou\n");
        }
    }
}