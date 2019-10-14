#pragma once
#include "token.h"
#include <vector>

using TType = Token::Type;

class Tokenizer {
    std::vector<Token> tokenList;

    const static char BOPS[];
    const static char UOPS[];
    const static char DELIMETERS[];
    
    TType checkType(char c);

public:
    void parseInput(std::string& input);

    auto& getTokenList() {
        return tokenList;
    };

    Tokenizer() {
        tokenList = std::vector<Token>();
    };

    void printTokens();
};
