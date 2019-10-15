#include "syntax_parser.h"
#include <iostream>
#include <stdexcept>

int SyntaxParser::evaluate(std::vector<Token>& tokensList) {
   iter = tokensList.begin();
   end = tokensList.end();

   expPlusMinus();
   _expPlusMinus();
   
   if (operands.size() != 1 || iter != end)
       throw std::invalid_argument("Invalid syntax");

   return operands.top();
};

void SyntaxParser::expPlusMinus() {
    expMultDiv();
    _expPlusMinus();
};

void SyntaxParser::_expPlusMinus() {
    if (iter != end && (!iter->getValue().compare("+") || 
                !iter->getValue().compare("-"))) {
        Token op = *iter;
        iter++;
        expPlusMinus();
        if (operands.size() < 2)
            throw std::invalid_argument("Invalid syntax: not enough operands");
        int op2 = operands.top();
        operands.pop();
        int op1 = operands.top();
        operands.pop();
        operands.push(op.getBinOp()(op1, op2));
    }
};

void SyntaxParser::expMultDiv() {
    expUnary();
    _expMultDiv();
};

void SyntaxParser::_expMultDiv() {
    if (iter != end && (!iter->getValue().compare("/") || 
                !iter->getValue().compare("*"))) {
        Token op = *iter;
        iter++;
        expMultDiv();
        if (operands.size() < 2)
            throw std::invalid_argument("Invalid syntax: not enough operands");
        int op2 = operands.top();
        operands.pop();
        int op1 = operands.top();
        operands.pop();
        operands.push(op.getBinOp()(op1, op2));
    }
};

void SyntaxParser::expUnary() {
   _expUnary();
   expConst();
};

void SyntaxParser::_expUnary() {
    if (iter != end && !iter->getValue().compare("-")) {
        Token op = *iter;
        iter++;
        expUnary();
        if (operands.size() < 1)
            throw std::invalid_argument("Invalid syntax: not enough operands");
        int op1 = operands.top();
        operands.pop();
        operands.push(-op1);
    }
};

void SyntaxParser::expConst() {
    if (iter != end && iter->getType() == Token::NUMBER) {
        operands.push(std::stoi(iter->getValue()));
        iter++;
    }
};
