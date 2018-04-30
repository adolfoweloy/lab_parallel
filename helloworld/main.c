//
// main.c
//
// Just a hello world example on how to create and start pthreds. This source code
// is inspired on the example provided by Peter Pacheco on his book:
// "An Introduction to Parallel Programming".
//
// Created by Adolfo Eloy on 29/04/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* hello(void*);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("usage: main <num_threads>\n");
    exit(1);
  }

  long num_threads = strtol(argv[1], NULL, 10);
  pthread_t* threads = malloc(sizeof(pthread_t) * num_threads);

  for (long range = 0; range < num_threads; range++)
    pthread_create(&threads[range], NULL,&hello, (void*) range);

  for (long range = 0; range < num_threads; range++)
    pthread_join(threads[range], NULL);

  printf("hello from main thread\n");

  exit(0);
}

void* hello(void* params)
{
  long range = (long) params;
  printf("running thread %ld\n", range);
  return NULL;
}
