#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/matrix.h"
#include <iostream>
#include <random>

static const size_t rows = 3;
static const size_t cols = 4;
static std::default_random_engine generator;
static std::uniform_int_distribution<int> distribution(-100, 100);
static std::uniform_int_distribution<size_t> rand_row(0, rows-1);
static std::uniform_int_distribution<size_t> rand_column(0, cols-1);


TEST_CASE("matrix", "[Matrix]") {
    int init = distribution(generator);
    Matrix m(rows, cols, init);

    REQUIRE(m.getRows() == rows);
    REQUIRE(m.getColumns() == cols);


    SECTION ("indexing check") {
        int value = distribution(generator);
        size_t i = rand_row(generator), j = rand_column(generator);
        m[i][j] = value;

        REQUIRE(m.getRows() == rows);
        REQUIRE(m.getColumns() == cols);
        REQUIRE(m[i][j] == value);

        int getval = m[i][j];
        REQUIRE(getval == value);
        
    }
    
    SECTION("initialization check") {
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                REQUIRE(m[i][j] == init);
    }

    SECTION ("multiply on number") {
        int value = distribution(generator);
        m *= value;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                REQUIRE(m[i][j] == init * value);
    }
    
    SECTION ("comparison") {
        Matrix m2(rows, cols, init);
        REQUIRE((m == m2));
        size_t i = rand_row(generator), j = rand_column(generator);
        int value = distribution(generator);
        m2[i][j] = value;
        REQUIRE((m != m2));
    }

};
