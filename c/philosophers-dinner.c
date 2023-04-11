#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5                            /* numero de filosofos */
#define LEFT (philosopher + N - 1) % N /* numero do vizinho a esquerda de i */
#define RIGHT (philosopher + 1) % N    /* numero do vizinho a direita de i */
#define THINKING 0                     /* o filosofo esta pensando */
#define HUNGRY 1                       /* o filosofo esta tentando pegar garfos */
#define EATING 2                       /* o filosofo esta comendo */
#define ERROR (status != 0)

int state[N];          /* arranjo para controlar o estado de cada um */
pthread_mutex_t mutex; /* exclusao mutua para as regioes criticas */
sem_t semaphores[N];   /* um semaforo por filosofo */
int current_philosopher = 0;

void think(int philosopher)
{
    printf("philosopher %d is THINKING\n", philosopher);
}

void eat(int philosopher)
{

    printf("philosopher %d is EATING\n", philosopher);
}

void test(int philosopher)
{
    if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[philosopher] = EATING;
        sem_post(&semaphores[philosopher]);
    }
}

void take_forks(int philosopher)
{
    pthread_mutex_lock(&mutex);         /* entra na regiao critica */
    state[philosopher] = HUNGRY;        /* registra que o filosofo esta faminto */
    test(philosopher);                  /* tenta pegar dois garfos */
    pthread_mutex_unlock(&mutex);       /* sai da regiao critica */
    sem_wait(&semaphores[philosopher]); /* bloqueia se os garfos nao foram pegos */
}

void put_forks(int philosopher)
{
    pthread_mutex_lock(&mutex);    /* entra na regiao critica */
    state[philosopher] = THINKING; /* o filosofo acabou de comer */
    test(LEFT);                    /* ve se o vizinho da esquerda pode comer agora */
    test(RIGHT);                   /* ve se o vizinho da direita pode comer agora */
    pthread_mutex_unlock(&mutex);  /* sai da regiao critica */
}

void philosopher(int i)
{
    state[i] = THINKING;
    while (1)
    {
        think(i);
        take_forks(i); /* pega dois garfos ou bloqueia */
        eat(i);
        put_forks(i); /* devolve os dois garfos a mesa */
    }
}

void *philosopher_init(void *)
{
    philosopher(current_philosopher++);
}

void main(void)
{
    pthread_t philosopher_thread[N];
    int status = 0;
    pthread_mutex_init(&mutex, 0);
    for (int i = 0; i < N; i++)
    {
        status = sem_init(&semaphores[i], 0, 0);
        if (ERROR)
            return;
    }
    for (int i = 0; i < N; i++)
    {
        pthread_create(&philosopher_thread[i], 0, philosopher_init, 0);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosopher_thread[i], 0);
    }
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&semaphores[i]);
    }
    pthread_mutex_destroy(&mutex);
}