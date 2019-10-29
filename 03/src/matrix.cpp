#include "matrix.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>

Matrix::Matrix (size_t r, size_t c): 
    rows(r), cols(c), matrix(new int[r*c]()) {}

Matrix::Matrix(size_t r, size_t c, int init): 
    rows(r), cols(c) {
    matrix = new int[r*c]; 
    std::fill_n(matrix, rows * cols, init);
}

Matrix::Matrix(size_t r, size_t c, int *m): rows(r), cols(c), matrix(m) {}

Matrix::~Matrix() {
    delete[] matrix;
}


bool Matrix::operator== (const Matrix &matr) {
    if (rows != matr.getRows() || cols != matr.getColumns())
        return false;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (matrix[i * cols + j] != matr.matrix[i * cols + j])
                return false;
    return true;
};

bool Matrix::operator!= (const Matrix &matr) {
    return !(*this == matr);
}
    
Matrix& Matrix::operator*= (int n) {
    for (size_t i = 0; i < rows * cols; i++)
        matrix[i] *= n;
    return *this; 
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getColumns() const {
    return cols;
}

Matrix::Row::Row(size_t c, int *r): cols(c), row(r) {};

int& Matrix::Row::operator[] (size_t i) {
    if (i >= cols)
        throw std::out_of_range("");
    return row[i];
}
    
Matrix::Row Matrix::operator[] (size_t i) {
    if (i >= rows) {
        throw std::out_of_range("");
    } 
    return Row(cols, &matrix[i * cols]);
}
