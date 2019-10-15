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

    const std::string& getValue() const {
        return value;
    };

    Type getType() const {
        return type;
    };

    const BinOp& getBinOp() const {
        return binOp;
    };

    Token (std::string& str, Type t, const BinOp& bo): 
        value(str), type(t), binOp(bo) {};

private:
    std::string value;
    Type type;
    BinOp binOp;
};
