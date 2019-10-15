#include "tokenizer.h"
#include <iostream>
#include <map>
#include <cctype>
#include <stdexcept>

std::map<char, BinOp> Tokenizer::BOPS = {
    {'+', [] (int a, int b) { return a + b; } }, 
    {'-', [] (int a, int b) { return a - b; } }, 
    {'*', [] (int a, int b) { return a * b; } }, 
    {'/', [] (int a, int b) { return a / b; } }
};
const char Tokenizer::UOPS[] = {'-'};
const char Tokenizer::DELIMETERS[] = {' '};

void Tokenizer::parseInput(const char *input) {
    std::string lex;
    TType prevType = Token::DELIM;
    for (const char *c = input; *c != '\0'; ++c) {
        TType curType = checkType(*c);
        if (curType != Token::DELIM && ((curType == prevType && prevType != Token::OP) 
                    || prevType == Token::DELIM)) 
            lex.push_back(*c);
        else if (!lex.empty()){
            tokenList.emplace_back(lex, prevType, ((prevType == Token::OP) ? 
                    BOPS[lex[0]] : [] (int a, int b) {return 0;}));
            lex.clear();
            if (curType != Token::DELIM)
                lex.push_back(*c);
        }
        prevType = curType;
    }
    
    if (!lex.empty()){
        tokenList.emplace_back(lex, prevType, ((prevType == Token::OP) ? 
                    BOPS[lex[0]] : [] (int a, int b) {return 0;}));
    }
};

Token::Type Tokenizer::checkType(const char c) {
    for (auto const& it : BOPS)
        if (it.first == c)
            return Token::OP;
    for (const char& it: DELIMETERS)
        if (it == c)
            return Token::DELIM;
    if (std::isdigit(c))
        return Token::NUMBER;
    throw std::invalid_argument(std::string("Invalid character: '") + c + "'");
};

void Tokenizer::printTokens() {
    for (Token& t: tokenList)
        std::cout << t.getValue() << " : " 
            << ((t.getType() == Token::OP) ? "OP" : "NUMBER") << std::endl;
};
