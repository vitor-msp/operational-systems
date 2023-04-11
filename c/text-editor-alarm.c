#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

char text[16 * 4] = "";

void *input(void *)
{
    char input[16];
    while (1)
    {
        printf(">> ");
        scanf("%s", input);
        strcat(text, input);
        printf("input: %s\n", input);
    }
}

void save(int)
{
    signal(SIGALRM, save);
    printf("\nsaved: %s\n", text);
    strcpy(text, "");
    alarm(3);
}

int main(void)
{
    pthread_t input_thread, save_thread;
    pthread_create(&input_thread, 0, input, 0);
    save(0);
    pthread_join(input_thread, 0);
    return 0;
}