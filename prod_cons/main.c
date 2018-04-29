//
//  main.c
//  producer_consumer
//
//  Created by Adolfo Eloy on 29/04/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20
#define QUEUE_SIZE 5

int* queue;
int queue_size;

pthread_cond_t condp;
pthread_cond_t condc;

pthread_mutex_t mutex;

bool queue_full(void);
bool queue_empty(void);
void* producer(void*);
void *consumer(void*);

int main(int argc, const char * argv[]) {
    queue_size = 0;
    queue = malloc(sizeof(int) * QUEUE_SIZE);
    memset(queue, 0x00, QUEUE_SIZE*sizeof(int));

    if (!queue) {
        printf("unable to allocate memory for queue\n");
        exit(1);
    }

    srand((unsigned) time(0));
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);

    pthread_t thread_producer;
    pthread_t thread_consumer;

    pthread_create(&thread_consumer, NULL, &consumer, NULL);
    pthread_create(&thread_producer, NULL, &producer, NULL);

    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);

    pthread_cond_destroy(&condp);
    pthread_cond_destroy(&condc);
    pthread_mutex_destroy(&mutex);

    exit(0);
}

void* producer(void* params) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);
        while (queue_full())
            pthread_cond_wait(&condp, &mutex);

        int val = rand() % 100;
        printf("producing queue[%d] = %d\n", queue_size, val);
        queue[queue_size] = val;
        queue_size++;

        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void* params) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);
        while (queue_empty())
            pthread_cond_wait(&condc, &mutex);

        int val = queue[queue_size-1];
        printf("consuming queue[%d] = %d\n", queue_size-1, val);
        queue_size--;

        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

bool queue_full() {
    return queue_size == QUEUE_SIZE;
}

bool queue_empty() {
    return queue_size == 0;
}
