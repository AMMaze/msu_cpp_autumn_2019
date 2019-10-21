#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/LinearAllocator.h"

#define _INT(x) sizeof(int) * (x)

TEST_CASE("allocating memory", "[LinearAllocator]") {

    LinearAllocator la = LinearAllocator(_INT(10));

    REQUIRE(la.size() == 0);
    REQUIRE(la.capacity() == _INT(10));

    size_t mem1 = 5, mem2 = 4, mem3 = 3;
    char *p1, *p2, *p3;
    SECTION ("allocating first chunk of memory") {
        p1 = la.alloc(_INT(mem1));

        REQUIRE(la.size() == _INT(mem1));
        REQUIRE(la.capacity() == _INT(10));

    }
    
    SECTION ("allocating second chunk of memory") {
        p1 = la.alloc(_INT(mem1));
        p2 = la.alloc(_INT(mem2));

        REQUIRE(la.size() == _INT(mem2 + mem1));
        REQUIRE(la.capacity() == _INT(10));

    }
    
    SECTION ("allocating third chunk of memory") {
        p1 = la.alloc(_INT(mem1));
        p2 = la.alloc(_INT(mem2));
        p3 = la.alloc(_INT(mem3));

        REQUIRE(la.size() == _INT(mem1 + mem2));
        REQUIRE(la.capacity() == _INT(10));
        REQUIRE(p3 == nullptr);
    }

    SECTION ("checking data in allocated memory") {
        p1 = la.alloc(_INT(mem1));
        for (size_t i = 0; i < mem1; i++) 
            p1[i] = i * mem1;

        p2 = la.alloc(_INT(mem2));
        for (size_t i = 0; i < mem2; i++) 
            p2[i] = i * mem2;

        p3 = la.alloc(_INT(mem3));

        for (size_t i = 0; i < mem1; i++) 
            REQUIRE(p1[i] == i * mem1);
        for (size_t i = 0; i < mem2; i++) 
            REQUIRE(p2[i] == i * mem2);
    }

    SECTION ("resetting allocator") {
        p1 = la.alloc(_INT(mem1));
        for (size_t i = 0; i < mem1; i++) 
            p1[i] = i * mem1;

        p2 = la.alloc(_INT(mem2));
        for (size_t i = 0; i < mem2; i++) 
            p2[i] = i * mem2;
        la.reset();

        REQUIRE(la.size() == 0);
        REQUIRE(la.capacity() == _INT(10));

    }
};
