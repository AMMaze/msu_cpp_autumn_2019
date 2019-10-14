#include "tokenizer.h"
#include "syntax_parser.h"
#include <iostream>

int main() {
    std::string str = "3 * 2 +  1 - 4 * - 2";

    Tokenizer tokenizer;

    tokenizer.parseInput(str);
    tokenizer.printTokens(); 

    SyntaxParser syntaxParser;

    std::cout << syntaxParser.evaluate(tokenizer.getTokenList()) << std::endl;

    return 0;

};
