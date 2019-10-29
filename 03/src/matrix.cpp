#include "matrix.h"
#include <cstring>
#include <stdexcept>

Matrix::Matrix (uint r, uint c): rows(r), cols(c) {
    matrix = new int[r*c]();   
}

Matrix::Matrix(uint r, uint c, int *m): rows(r), cols(c), matrix(m) {}

Matrix::~Matrix() {
    delete[] matrix;
}


bool Matrix::operator== (Matrix &matr) {
    if (rows != matr.getRows() || cols != matr.getColumns())
        return false;
    for (uint i = 0; i < rows; i++)
        for (uint j = 0; j < cols; j++)
            if (matrix[i * cols + j] != matr[i][j])
                return false;
    return true;
};

bool Matrix::operator!= (Matrix &matr) {
    if (rows != matr.getRows() || cols != matr.getColumns())
        return true;
    for (uint i = 0; i < rows; i++)
        for (uint j = 0; j < cols; j++)
            if (matrix[i * cols + j] != matr[i][j])
                return true;
    return false;
}
    
Matrix& Matrix::operator*= (int n) {
    for (uint i = 0; i < rows * cols; i++)
        matrix[i] *= n;
    return *this; 
}

uint Matrix::getRows() const {
    return rows;
}

uint Matrix::getColumns() const {
    return cols;
}

Matrix::Row::Row(uint c, int *r): cols(c), row(r) {};

int& Matrix::Row::operator[] (uint i) {
    if (i >= cols)
        throw std::out_of_range("");
    return row[i];
}
    
Matrix::Row Matrix::operator[] (uint i) {
    if (i >= rows) {
        throw std::out_of_range("");
    } 
    return Row(cols, &matrix[i * cols]);
}
