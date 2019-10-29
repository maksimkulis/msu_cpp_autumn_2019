#include <iostream>
#include <stdexcept>

#include "matrix.h"

#define MATRROW 5
#define MATRCOL 6

int main()
{
    Matrix m1(MATRROW, MATRCOL);
    Matrix m2(MATRROW, MATRCOL);
    Matrix m3(4, 4);
    for (size_t i = 0; i < MATRCOL * MATRROW; i++) {
        m1[i/MATRCOL][i%MATRCOL] = i;
        m2[i/MATRCOL][i%MATRCOL] = i;
        if (m1[i/MATRCOL][i%MATRCOL] != i) {
            std::cout << "Test0 false\n";
            break;
        }
    }

    if (m1.getRows() != MATRROW || m1.getColumns() != MATRCOL) {
        std::cout << "Test1 false\n";
    }

    if (m1 != m2) {
        std::cout << "Test2 false\n";
    }

    if (m1 == m3) {
        std::cout << "Test3 false\n";
    }

    m2[0][0] = 100;
    if (m1 == m2) {
        std::cout << "Test4 false\n";
    }

    if (!(m1 != m2)) {
        std::cout << "Test5 false\n";
    }

    m1 *= 5;
    for (size_t i = 0; i < MATRCOL * MATRROW; i++) {
        if (m1[i/MATRCOL][i%MATRCOL] != 5 * i) {
            std::cout << "Test6 false\n";
        }
    }

    size_t catched = 0;
    try {
        m1[MATRROW + 1][MATRCOL - 1];
    } catch (std::out_of_range) {
        catched++;
    }

    try {
        m1[MATRROW - 1][MATRCOL + 1];
    } catch (std::out_of_range) {
        catched++;
    }
    
    if (catched != 2) {
        std::cout << "Test7 false\n";
    }
    return 0;
}
