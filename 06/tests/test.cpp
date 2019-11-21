#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/format.h"
#include <iostream>
#include <random>
#include <string>
#include <stdexcept>

std::default_random_engine generator;
std::uniform_int_distribution<uint64_t> distribution(0, 10000000);
std::uniform_int_distribution<int> float_distribution(0, 1);


TEST_CASE("format", "[format]") {

    SECTION ("strings/char/int/float") {
       
        std::string s1 = "(string)";
        char s2[] = "(char*)";
        const char s3[] = "(const char*)";
        int s4 = 123456;
        float s5 = 1.23456;

        auto out1 = format("{0}, {1}, {2}, {3}, {4}", s1, s2, s3, s4, s5);
        auto out2 = format("{0}, {1}, {1}, {0}", s2, s4);
        auto out3 = format("{3}, {2}, {1}, {0}", s3, s4, s1, s5);

        REQUIRE(out1 == "(string), (char*), (const char*), 123456, 1.234560");
        REQUIRE(out2 == "(char*), 123456, 123456, (char*)");
        REQUIRE(out3 == "1.234560, (string), 123456, (const char*)");

    };

    SECTION("exceptions") {
        try {
            auto text = format("{0}, {1}", 1);
        } catch (std::runtime_error& e) {
            REQUIRE(e.what() == std::string("Incorrect number of arguments"));
        }
        
        try {
            auto text = format("{0}", 1, 2);
        } catch (std::runtime_error& e) {
            REQUIRE(e.what() == std::string("Incorrect number of arguments"));
        }
    };
        
};
