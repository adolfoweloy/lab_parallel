//
//  main.c
//  matrixvector
//
//  Performs the multiplication of a matrix A by some vector X.
//  Inspired on Peter Pacheco book (An Introduction to Parallel Programming).
//
//  Created by Adolfo Eloy on 29/04/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// declares the size of matrix/vector
int m, n;

// number of threads to carry out matrix-vector multiplication
int num_threads;
pthread_t *threads;

// matrices
int **A;
int **x;
int **y;

// prototypes
void* p_matrix_vector_mult(void*);

// print_matrix must receive three arguments
// array to be printed + (number of rows and cols)
void print_matrix(int**, int, int);

// generates a matrix with random values
// first argument is a pointer to a matrix
// second and third arguments must be the number of rows and cols respectively.
void matrix_gen(int**, int, int);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("usage: main <m> <n> <num_threads>\n");
        exit(1);
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    num_threads = atoi(argv[3]);
    threads = malloc(sizeof(pthread_t) * num_threads);

    srand((unsigned) time(0));

    // allocating matrix memory
    A = malloc(sizeof(int) * m * n);
    x = malloc(sizeof(int) * n);
    y = malloc(sizeof(int) * m);

    // generate matrices
    matrix_gen(A, m, n);
    matrix_gen(x, n, 1);
    matrix_gen(y, m, 1);

    // print matrices
    print_matrix(A, m, n);
    print_matrix(x, n, 1);

    // runs the matrix-vector multiplication in a parallel way
    for (long i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, p_matrix_vector_mult, (void*) i);

    for (long i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    // prints the result
    print_matrix(y, m, 1);

    // clearing dangling pointers
    free(threads); threads = NULL;
    free(A); A = NULL;
    free(x); x = NULL;
    free(y); y = NULL;

    exit(0);
}

void* p_matrix_vector_mult(void *params)
{
    long rank = (long) params;
    int offset = m / num_threads;
    long first_row = rank * offset;
    long last_row = (rank + 1) * offset - 1;

    for (long i = first_row; i < last_row; i++)
    {
        y[i] = malloc(sizeof(int));
        y[i][0] = 0;
        for (long j = 0; j < n; j++)
        {
            y[i][0] += A[i][j] * x[j][0];
        }

    }

    return NULL;
}

void print_matrix(int **array, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    }
    printf("\n");
}

void matrix_gen(int **array, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        array[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
          array[i][j] = rand() % 100;
        }

    }
}
