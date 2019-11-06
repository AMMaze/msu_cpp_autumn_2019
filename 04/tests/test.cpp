#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/bigint.h"
#include <iostream>
#include <random>
#include <string>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(-100000, 100000);


TEST_CASE("bigint", "[BigInt]") {

    SECTION ("constructors") {
        int v1 = distribution(generator);
        
        BigInt bi1(v1);
        BigInt bi2(bi1);
        BigInt bi3 = BigInt();

        std::ostringstream str;
        str << bi1;
        REQUIRE(str.str() == std::to_string(v1));
        str.str(std::string());
        str << bi2;
        REQUIRE(str.str() == std::to_string(v1));
        str.str(std::string());
        str << bi3;
        REQUIRE(str.str() == std::string("0"));
        
    }

    SECTION ("assignments") {
        int v1 = distribution(generator);

        BigInt bi1(v1);
        BigInt bi2;
        bi2 = bi1;
        BigInt bi3;
        bi3 = v1;
        
        std::ostringstream str;
        str << bi2;
        REQUIRE(str.str() == std::to_string(v1));
        str.str(std::string());
        str << bi3;
        REQUIRE(str.str() == std::to_string(v1));
    }
    
    SECTION ("arithmetics") {
        int v1 = distribution(generator);
        int v2 = distribution(generator);
        int v3 = distribution(generator);

        BigInt bi1(v1), bi2(v2), bi3(v3);

        std::ostringstream res1, res2, res3, res4, res5;
        res1 << (bi1 + bi2);
        REQUIRE(res1.str() == std::to_string(v1 + v2));
        res2 << (bi1 - bi2);
        REQUIRE(res2.str() == std::to_string(v1 - v2));
        res3 << (-bi3);
        REQUIRE(res3.str() == std::to_string(-v3));
        res4 << (bi1 + v1);
        REQUIRE(res4.str() == std::to_string(v1 + v1));
        res5 << (bi1 - v1);
        REQUIRE(res5.str() == std::to_string(0));
    }

    SECTION ("comparisons") {
        int v1 = distribution(generator);
        int v2 = distribution(generator);
        int v3 = distribution(generator);
        
        BigInt bi1(v1), bi2(v2), bi3(v3);

        REQUIRE((bi1 == bi1));
        REQUIRE((bi1 != bi2) == (v1 != v2));
        REQUIRE((bi2 < bi3) == (v2 < v3));
        REQUIRE((bi1 <= bi3) == (v1 < v3));
        REQUIRE((bi2 > bi1) == (v2 > v1));
        REQUIRE((bi3 >= bi1) == (v3 >= v1));
        
        REQUIRE((bi1 == v1));
        REQUIRE((bi1 != v2) == (v1 != v2));
        REQUIRE((bi2 < v3) == (v2 < v3));
        REQUIRE((bi1 <= v3) == (v1 < v3));
        REQUIRE((bi2 > v1) == (v2 > v1));
        REQUIRE((bi3 >= v1) == (v3 >= v1));
    }
};
