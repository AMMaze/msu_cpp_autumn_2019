#include "src/matrix.h"
#include <cstddef>
#include <cassert>

int main() {

    const size_t rows = 5;
    const size_t cols = 5;

    Matrix m(rows, cols);

    
    assert(m.getRows() == 5);
    assert(m.getColumns() == 5);

    m[1][2] = 5; 
    assert(m[1][2] == 5);

    int x = m[4][1];

    assert(x == 0);

    m *= 3;
    assert(m[1][2] == 15);

    Matrix m1(rows, cols);
    m1[1][2] = 15;
    assert(m == m1);
    
    return 0;
};
