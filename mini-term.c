#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PIPE "|"
#define READ (fd[0])
#define WRITE (fd[1])
#define FILHO1 (pid1 == 0)
#define PAI1 (pid1 > 0)
#define FILHO2 (pid2 == 0)
#define PAI2 (pid2 > 0)
#define STDIN 0
#define STDOUT 1

char text1[16], text2[16], text3[16], text4[16], text5[16];
char *file1, *file2, *args1, *args2;
int fd[2], pid1, pid2, statloc1, statloc2;

void pipe_routine(void)
{
    file1 = &text1[0];
    args1 = &text2[0];
    file2 = &text4[0];
    args2 = &text5[0];
    pipe(fd);
    pid1 = fork();
    if (FILHO1)
    {
        close(READ);
        dup2(WRITE, STDOUT);
        close(WRITE);
        execlp(file1, file1, args1, (char *)0);
    }
    if (PAI1)
    {
        close(WRITE);
        pid2 = fork();
        if (FILHO2)
        {
            dup2(READ, STDIN);
            close(READ);
            execlp(file2, file2, args2, (char *)0);
        }
        if (PAI2)
        {
            close(READ);
            waitpid(pid1, &statloc1, 0);
            waitpid(pid2, &statloc2, 0);
        }
    }
}

void single_file_routine(void)
{
    file1 = &text1[0];
    args1 = &text2[0];
    pid1 = fork();
    if (FILHO1)
    {
        execlp(file1, file1, args1, (char *)0);
    }
    if (PAI1)
    {
        waitpid(pid1, &statloc1, 0);
    }
}

int main(void)
{
    while (1)
    {
        printf(">> ");
        scanf("%s %s %s %s %s", text1, text2, text3, text4, text5);
        if (strcmp(text3, PIPE) == 0)
        {

            pipe_routine();
            continue;
        }
        single_file_routine();
    }
}