#include "LinearAllocator.h"

LinearAllocator::LinearAllocator (std::size_t maxSize): 
    maxSize(maxSize), length(0), start(new char(maxSize)) {};

char* LinearAllocator::alloc (std::size_t size) {
    if (maxSize - length >= size) {
        char* p = start + length;
        length += size;
        return p;
    }
    return nullptr;
};

void LinearAllocator::reset () {
    length = 0;
};

std::size_t LinearAllocator::size() {
    return length;
};

std::size_t LinearAllocator::capacity() {
    return maxSize;
};

LinearAllocator::~LinearAllocator() {
    delete start;
};
