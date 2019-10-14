#include "syntax_parser.h"
#include <iostream>

int SyntaxParser::evaluate(std::vector<Token>& tokensList) {
   iter = tokensList.begin();
   end = tokensList.end();

   expPlusMinus();
   _expPlusMinus();
   
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
        std::cout << "stack size: (+ -)" << operands.size() << std::endl;
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
        std::cout << op.getValue() << std::endl;
        iter++;
        expMultDiv();
        std::cout << "stack size: (/ *)" << operands.size() << std::endl;
        int op2 = operands.top();
        operands.pop();
        int op1 = operands.top();
        std::cout << op1 << "  " << op2 << std::endl;
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
        std::cout << op.getValue() << std::endl;
        iter++;
        expUnary();
        std::cout << "stack size: (un)" << operands.size() << std::endl;
        int op1 = operands.top();
        std::cout << op1 << std::endl;
        operands.pop();
        operands.push(-op1);
    }
};

void SyntaxParser::expConst() {
    if (iter != end && iter->getType() == Token::NUMBER) {
        operands.push(std::stoi(iter->getValue()));
        std::cout << std::stoi(iter->getValue()) << " stack size : " << operands.size() << std::endl;
        iter++;
    }
};
