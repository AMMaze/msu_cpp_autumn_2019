#pragma once
#include "token.h"
#include <vector>
#include <map>

using TType = Token::Type;

class Tokenizer {
    std::vector<Token> tokenList;

    //can't pass const members to Token constructor
    static std::map<char, BinOp> BOPS;
    const static char UOPS[];
    const static char DELIMETERS[];
    
    TType checkType(char c);

public:
    void parseInput(char *input);

    auto& getTokenList() {
        return tokenList;
    };

    Tokenizer() {
        tokenList = std::vector<Token>();
    };

    void printTokens();
};
