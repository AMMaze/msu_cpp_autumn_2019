#pragma once

#include<string>
#include <functional>

using BinOp = std::function<int(int, int)>;

class Token {
public:
    enum Type {
        NUMBER,
        OP,
        UOP,
        DELIM
    };

    std::string& getValue() {
        return value;
    };

    Type getType() {
        return type;
    };

    BinOp& getBinOp() {
        return binOp;
    };

    Token (std::string& str, Type t, const BinOp& bo): 
        value(str), type(t), binOp(bo) {};

private:
    std::string value;
    Type type;
    BinOp binOp;
};
