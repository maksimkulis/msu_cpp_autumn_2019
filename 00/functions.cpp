#include "functions.h"
#include "timer.h"

#define ITTER_NUM 10

void warming_up(int** matrix, int N, int M) {
    for (int itteration = 0; itteration < ITTER_NUM; itteration++) {
        volatile int sum = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                sum += matrix[i][j];
            }
        }
    }
}

void sum_by_rows(int** matrix, int N, int M)
{
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sum += matrix[i][j];
        }
    }
}

void sum_by_colums(int** matrix, int N, int M)
{
    Timer t;
    volatile int sum = 0;
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            sum += matrix[i][j];
        }
    }
}
