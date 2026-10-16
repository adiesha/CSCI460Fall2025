#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define BUFFER_SIZE 5 // maximum items in the buffer

int in =0;
int out = 0;

int buffer[BUFFER_SIZE];

sem_t s;
sem_t n;
sem_t e;

void* consumer_func(void* arg) {
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&n);
        sem_wait(&s);
        int take = buffer[out];
        out = (out + 1)% BUFFER_SIZE;

        char buffertake[100];
        snprintf(buffertake, sizeof(buffertake), "%sConsuming take: %d%s\n",KRED, take, KNRM);
        write(STDOUT_FILENO, buffertake, strlen(buffertake));
        
        // char buffertake[100];
        // snprintf(buffertake, sizeof(buffertake), "%sConsumed %d items%s\n", KRED, i, KNRM);
        // write(STDOUT_FILENO, buffertake, strlen(buffertake));
        sem_post(&s);
        sem_post(&e);
    }
    return NULL;
}


void* producer_func(void* arg) {
    for (int i = 0; i < 10; i++)
    {
        int temp = rand() % 100;

        sem_wait(&e);
        sem_wait(&s);
        
        buffer[in] = temp;
        in = (in + 1) % BUFFER_SIZE;
        char log_msg[100];
        snprintf(log_msg, sizeof(log_msg), "%sProduced %d items, and latest value: %d %s\n", KGRN, i, temp, KNRM);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        sem_post(&s);
        sem_post(&n);
    }
    return NULL;
}


int main() {

    pthread_t producer, consumer;
    sem_init(&s, 0, 1); // second arguement (0) means shared between threads of the same process
                        // third 1 means the starting value of the semaphore
    sem_init(&e, 0, BUFFER_SIZE);
    sem_init(&n, 0, 0);


    pthread_create(&producer, NULL, producer_func, NULL);
    pthread_create(&consumer, NULL, consumer_func, NULL);


    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&s);
    sem_destroy(&n);
    sem_destroy(&e);

    return EXIT_SUCCESS;
}