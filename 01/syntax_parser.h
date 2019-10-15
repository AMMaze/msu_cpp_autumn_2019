#pragma once
#include "token.h"
#include <vector>
#include <stack>

class SyntaxParser {
    std::stack<int> operands;
    std::vector<Token>::const_iterator iter, end; 

    void expPlusMinus();
    void _expPlusMinus();

    void expMultDiv();
    void _expMultDiv();

    void expUnary();
    void _expUnary();

    void expConst();

public:
    int evaluate(const std::vector<Token>& tokensList);    

    SyntaxParser(): operands(std::stack<int>()) {};
};
