#include "tokenizer.h"

int main() {
    std::string str = "3 +  1 - 4 * 2";

    Tokenizer tokenizer;

    tokenizer.parseInput(str);
    tokenizer.printTokens(); 

    return 0;

};
