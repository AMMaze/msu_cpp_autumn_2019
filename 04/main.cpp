#include "src/bigint.h"
#include <iostream>

int main() {
    BigInt bi1(511);
    BigInt bi2(511);
    BigInt res = bi1 + 511;
    std::cout << res << std::endl;

    return 0;
};
