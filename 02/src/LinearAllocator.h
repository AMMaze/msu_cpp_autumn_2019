#pragma once
#include <cstddef>

class LinearAllocator {
    std::size_t maxSize;
    std::size_t length;
    char* start;

public:
    LinearAllocator(std::size_t maxSize);
    char* alloc(std::size_t size);
    void reset();

    std::size_t size();
    std::size_t capacity();

    ~LinearAllocator();
};
