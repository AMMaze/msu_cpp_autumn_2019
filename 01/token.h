#pragma once

#include<string>

class Token {
public:
    enum Type {
        NUMBER,
        OP,
        DELIM
    };

    std::string& getValue() {
        return value;
    };

    Type getType() {
        return type;
    };

    Token (std::string& str, Type t): value(str), type(t) {};

private:
    std::string value;
    Type type;
};
