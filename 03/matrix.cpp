#include <cstdlib>
#include <stdexcept>
#include <cstring>

#include "matrix.h"

Matrix::Matrix(size_t rows, size_t cols)
              : cols(cols)
              , rows(rows)
{
    data = new int[cols * rows];
}

Matrix::Row::Row(int* row, size_t cols)
                : row(row)
                , cols(cols)
{
}

Matrix::~Matrix()
{
    delete[] data;
}
Matrix::Row::~Row()
{
}

size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getColumns() const
{
    return cols;
}

const Matrix::Row Matrix::operator[](size_t row) const
{
    if (row >= 0 && row < rows) {
        return Row(data + row * cols, cols);
    } else {
        throw std::out_of_range("");
    }
}

Matrix::Row Matrix::operator[](size_t row)
{
    if (row >= 0 && row < rows) {
        return Row(data + row * cols, cols);
    } else {
        throw std::out_of_range("");
    }
}

int& Matrix::Row::operator[](size_t col)
{
    if (col >= 0 && col < cols) {
        return row[col];
    } else {
        throw std::out_of_range("");
    }
}

const int& Matrix::Row::operator[](size_t col) const
{
    if (col >= 0 && col < cols) {
        return row[col];
    } else {
        throw std::out_of_range("");
    }
}

bool Matrix::operator==(const Matrix& second_matr) const
{
    if (second_matr.getRows() != rows && second_matr.getColumns() != cols) {
        return false;
    }
    return !(memcmp(data, second_matr.data, cols * rows * sizeof(int)));
}

bool Matrix::operator!=(const Matrix& second_matr) const
{
    return !(*this == second_matr);
}

Matrix& Matrix::operator*=(int value)
{
    for (size_t i = 0; i < cols * rows; i++) {
        data[i] *= value;
    }
    return *this;
}
