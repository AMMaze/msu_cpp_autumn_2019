#pragma once
#include "token.h"
#include <vector>
#include <map>

using TType = Token::Type;

class Tokenizer {
    std::vector<Token> tokenList;

    const static std::map<char, BinOp> BOPS;
    const static char UOPS[];
    const static char DELIMETERS[];
    
    TType checkType(const char c);

public:
    void parseInput(const char *input);

    const auto& getTokenList() {
        return tokenList;
    };

    void printTokens();
};
