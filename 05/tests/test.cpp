#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/serializer.h"
#include "../src/deserializer.h"
#include "../src/data.h"
#include <iostream>
#include <random>
#include <string>
#include <sstream>

std::default_random_engine generator;
std::uniform_int_distribution<uint64_t> distribution(0, 10000000);
std::uniform_int_distribution<int> bool_distribution(0, 1);


TEST_CASE("serializer/deserializer", "[Serializer/Deserializer]") {

    SECTION ("serialize/deserialize") {
        Data data {distribution(generator), 
            static_cast<bool>(bool_distribution(generator)),
            distribution(generator)};

        std::stringstream ss;
        Serializer serializer(ss);
        serializer.save(data);

        std::string expected = std::to_string(data.a) + " " + 
            (data.b ? std::string("true") : std::string("false")) + " " +
            std::to_string(data.c);

        REQUIRE(ss.str() == expected);

        Data data_out{0, false, 0};

        Deserializer deserializer(ss);
        deserializer.load(data_out);

        REQUIRE(data.a == data_out.a);
        REQUIRE(data.b == data_out.b);
        REQUIRE(data.c == data_out.c);
        
    }
        
};
