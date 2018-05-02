//
//  main.c
//  critical_section
//
//  this program presents the access to variable sum in a concurrently manner.
//  this variable is updated by different threads, within the critical section.
//
//  the solution employed here was to use busy wait technique.
//
//  Created by Adolfo Eloy on 01/05/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long n;
double sum;
void* thread_sum(void* param);

int flag;
int thread_count;
pthread_t *threads;

int main(int argc, const char * argv[])
{
  flag = 1;
  n = 100000000;
  thread_count = 4;

  threads = malloc(sizeof(pthread_t) * thread_count);
  for (long i = 0; i < thread_count; i++)
    pthread_create(&threads[i], NULL, thread_sum, (void*) i);

  for (long i = 0; i < thread_count; i++)
    pthread_join(threads[i], NULL);

  printf("pi %f\n", 4 * sum);
}

void* thread_sum(void* param)
{
  long rank = (long) param;
  double factor;
  long long i;
  long long offset = n / thread_count;
  long long first = offset * rank;
  long long last  = first + offset;

  double _sum = 0.0;

  if (first % 2 == 0)
    factor = 1.0;
  else
    factor = -1.0;

  for (i = first; i < last;  i++, factor = -factor)
    _sum += factor / (2 * i + 1);

  // busy waiting
  while (flag != rank);
  sum += _sum;
  flag = (flag + 1) % thread_count;
  // end of busy waiting

  return NULL;
}
