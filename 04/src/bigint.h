#pragma once
#include <iostream>

class BigInt {
public:
    struct _bigInt {
        char *digit;
        _bigInt  *prev, *next;

        _bigInt();
        _bigInt(char d);
        _bigInt(char d, _bigInt *p);
        _bigInt(char d, _bigInt *p, _bigInt *n);
        ~_bigInt();
    };

    BigInt();
    BigInt(int n);
    BigInt(const BigInt& n);
    ~BigInt();

    BigInt& operator=(const Bigint& n);
    BigInt& operator=(int n);
    BigInt& operator+(const BigInt& n);
    BigInt& operator+(int n);
    BigInt& operator-(int n);
    BigInt& operator-(const BigInt& n);
    BigInt& operator-();

    bool operator==(const BigInt& n);
    bool operator!=(const BigInt& n);
    bool operator<(const BigInt& n);
    bool operator<=(const BigInt& n);
    bool operator>(const BigInt& n);
    bool operator>=(const BigInt& n);

    friend std::ostream &operator<<(std::ostream &os, const BigInt& obj);

private:
    _bigInt *numHigh, *numLow;
    int length;
    bool isPositive;
};
