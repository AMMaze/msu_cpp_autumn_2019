#pragma once
#include <iostream>

class BigInt {
public:
    struct _bigInt {
        _bigInt();
        _bigInt(char d);
        _bigInt(char d, _bigInt *p);
        _bigInt(char d, _bigInt *p, _bigInt *n);
        ~_bigInt();

        char getDigit();
        void setDigit(char d);
        _bigInt* getPrev();
        void setPrev(_bigInt* p);
        _bigInt* getNext();
        void setNext(_bigInt* p);

    private:
        char digit;
        _bigInt  *prev, *next;
    };

    BigInt();
    BigInt(int n);
    BigInt(const BigInt& n);
    ~BigInt();

    friend void swap(BigInt& first, BigInt& second);

    BigInt& operator=(const BigInt& n);
    BigInt& operator=(int n);
    BigInt operator+(const BigInt& n);
    BigInt operator+(int n);
    BigInt operator-(int n);
    BigInt operator-(const BigInt& n);
    BigInt operator-();

    bool operator==(const BigInt& n) const;
    bool operator!=(const BigInt& n) const;
    bool operator<(const BigInt& n) const;
    bool operator<=(const BigInt& n) const;
    bool operator>(const BigInt& n) const;
    bool operator>=(const BigInt& n) const;

    bool operator==(int n) const;
    bool operator!=(int n) const;
    bool operator<(int n) const;
    bool operator<=(int n) const;
    bool operator>(int n) const;
    bool operator>=(int n) const;

    friend std::ostream &operator<<(std::ostream &os, const BigInt& obj);

private:
    _bigInt *numHigh, *numLow;
    int length;
    bool isPositive;
};
