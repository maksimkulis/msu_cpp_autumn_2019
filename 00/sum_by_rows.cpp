#include <iostream>
#include "functions.h"

#define N 10000
#define M 10000

int main()
{
    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 3;
        }
    }
    // warming_up(matrix, N, M);
    std::cout << "Time for sum by rows: ";
    sum_by_rows(matrix, N, M);
    std::cout << std::endl;
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
