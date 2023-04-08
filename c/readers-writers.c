#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define READERS 2
#define WRITERS 2

pthread_mutex_t mutex; /* controla o acesso a ‘rc’ */
sem_t db;              /* controla o acesso a base de dados */
int rc = 0;            /* numero de processos lendo ou querendo ler */
char database[256] = "";

void think_up_data(void) {}

void use_data_read(void) {}

void write_data_base(void)
{
    printf("writing to database\n");
}

void read_data_base(void)
{
    printf("reading from database\n");
}

void *reader(void *)
{
    while (1)
    {
        pthread_mutex_lock(&mutex); /* obtem acesso exclusivo a ‘rc’ */
        rc++;                       /* um leitor a mais agora */
        if (rc == 1)
            sem_wait(&db);            /* se este for o primeiro leitor ... */
        pthread_mutex_unlock(&mutex); /* libera o acesso exclusivo a ‘rc’ */
        read_data_base();             /* acesso aos dados */
        pthread_mutex_lock(&mutex);   /* obtem acesso exclusivo a ‘rc’ */
        rc--;                         /* um leitor a menos agora */
        if (rc == 0)
            sem_post(&db);            /* se este for o ultimo leitor ... */
        pthread_mutex_unlock(&mutex); /* libera o acesso exclusivo a ‘rc’ */
        use_data_read();              /* regiao nao critica */
    }
}

void *writer(void *)
{
    while (1)
    {
        think_up_data();   /* regiao nao critica */
        sem_wait(&db);     /* obtem acesso exclusivo */
        write_data_base(); /* atualiza os dados */
        sem_post(&db);     /* libera o acesso exclusivo */
    }
}

void main(void)
{
    pthread_t readers[READERS], writers[WRITERS];
    pthread_mutex_init(&mutex, 0);
    sem_init(&db, 0, 1);
    for (int i = 0; i < WRITERS; i++)
    {
        pthread_create(&writers[i], 0, writer, 0);
    }
    for (int i = 0; i < READERS; i++)
    {
        pthread_create(&readers[i], 0, reader, 0);
    }
    for (int i = 0; i < WRITERS; i++)
    {
        pthread_join(writers[i], 0);
    }
    for (int i = 0; i < READERS; i++)
    {
        pthread_join(readers[i], 0);
    }
    sem_destroy(&db);
    pthread_mutex_destroy(&mutex);
}