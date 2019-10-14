#include "tokenizer.h"
#include <iostream>


const char Tokenizer::BOPS[] = {'+', '-', '*', '/'};
const char Tokenizer::UOPS[] = {'-'};
const char Tokenizer::DELIMETERS[] = {' '};

void Tokenizer::parseInput(std::string& input) {
    std::string lex;
    TType prevType = Token::DELIM;
    for (char c: input) {
        TType curType = checkType(c);
        if (curType != Token::DELIM && (curType == prevType || prevType == Token::DELIM)) 
            lex.push_back(c);
        else if (!lex.empty()){
            tokenList.emplace_back(lex, prevType);
            lex.clear();
            if (curType != Token::DELIM)
                lex.push_back(c);
        }
        prevType = curType;
    }
};

Token::Type Tokenizer::checkType(char c) {
    for (const char& it: BOPS)
        if (it == c)
            return Token::OP;
    for (const char& it: DELIMETERS)
        if (it == c)
            return Token::DELIM;
    return Token::NUMBER;
};

void Tokenizer::printTokens() {
    for (Token& t: tokenList)
        std::cout << t.getValue() << " : " 
            << ((t.getType() == Token::OP) ? "OP" : "NUMBER") << std::endl;
};
