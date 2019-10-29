#pragma once

class Matrix
{
public:
    class Row
    {
    public:
        Row(int* row, size_t cols);
        ~Row();
        int& operator[](size_t col);
        const int& operator[](size_t col) const;
    private:
        int* row;
        size_t cols;
    };

    Matrix(size_t rows, size_t cols);
    ~Matrix();
    size_t getRows() const;
    size_t getColumns() const;
    Row operator[](size_t row);
    const Row operator[](size_t row) const;
    bool operator==(const Matrix& second_matr) const;
    bool operator!=(const Matrix& second_matr) const;
    Matrix& operator*=(int value);
private:
    int* data;
    size_t cols;
    size_t rows;
};
