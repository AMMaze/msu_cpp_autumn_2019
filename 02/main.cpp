#include "src/LinearAllocator.h"
#include <iostream>
#include <cassert>
#include <string>

int main() {
    LinearAllocator la = LinearAllocator(sizeof(int) * 10);

    int* i1 = (int*) la.alloc(sizeof(int)*5);
    for (int i = 0; i < 5; i++) 
        i1[i] = i * 5;

    int* i2 = (int*) la.alloc(sizeof(int)*4);
    for (int i = 0; i < 4; i++) 
        i2[i] = i * 4;

    int* i3 = (int*) la.alloc(sizeof(int)*2);
    
    for (int i = 0; i < 5; i++) 
        assert(i1[i] == i * 5);
    
    for (int i = 0; i < 4; i++) 
        assert(i2[i] == i * 4);

    assert(i3 == nullptr);

    return 0;
};
