#include "tokenizer.h"
#include "syntax_parser.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {

    if (argc != 2)
        return 1;

    Tokenizer tokenizer;
    SyntaxParser syntaxParser;
    try {
        tokenizer.parseInput(argv[1]);
        //tokenizer.printTokens(); 
        std::cout << syntaxParser.evaluate(tokenizer.getTokenList()) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what()  << std::endl;
    }

    return 0;
};
