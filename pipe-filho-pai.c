#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1
#define STDOUT 1

int main()
{
    int n, fd[2];
    pid_t pid;
    if (pipe(fd) < 0)
    {
        fprintf(stderr, "Erro no tubo\n");
        _exit(1);
    }
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "Erro no fork\n");
        _exit(1);
    }
    if (pid > 0)
    { /* processo pai */
#define MAX 128
        char line[MAX];
        close(fd[WRITE]);
        printf("pai antes da leitura\n");
        n = read(fd[READ], line, MAX);
        printf("pai depois da leitura\n");
        write(STDOUT, &line[0], n);
        close(fd[READ]);
        kill(pid, SIGKILL); /* elimina processo descendente */
        _exit(0);
    }
    if (pid == 0)
    { /* processo filho */
#define LEN 8
        char msg[LEN] = {'B', 'o', 'm', ' ', 'd', 'i', 'a', '\n'};
        close(fd[READ]);
        printf("filho antes da escrita\n");
        write(fd[WRITE], &msg[0], LEN);
        printf("filho depois da escrita\n");
        close(fd[WRITE]);
        pause();
    }
}