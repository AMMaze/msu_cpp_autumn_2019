#include "tokenizer.h"
#include "syntax_parser.h"
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc != 2)
        return 1;

    Tokenizer tokenizer;

    tokenizer.parseInput(argv[1]);
    tokenizer.printTokens(); 

    SyntaxParser syntaxParser;

    std::cout << syntaxParser.evaluate(tokenizer.getTokenList()) << std::endl;

    return 0;

};
