#include <cstring>

class Matrix {
    size_t rows, cols;
    int *matrix;

    class Row {
        size_t cols;
        int *row;
    public:
        Row(size_t c, int *r);
        int& operator[] (size_t i);
    };

public:
    Matrix(size_t r, size_t c);
    Matrix(size_t r, size_t c, int init);
    Matrix(size_t r, size_t c, int *m);
    ~Matrix();

    bool operator== (const Matrix &matr);
    bool operator!= (const Matrix &matr);
    Matrix& operator*= (int n);

    size_t getRows() const;
    size_t getColumns() const;

    Row operator[] (size_t i);
};
