#include "bigint.h"
#include <cmath>
#include <stdlib.h> 
#include <string>

using _bInt = BigInt::_bigInt;

/*
 *  _bigInt constructors/destructors
 */
_bInt::_bigInt(): 
    digit(0), prev(nullptr), next(nullptr) {
}

_bInt::_bigInt(char d): 
    digit(d), prev(nullptr), next(nullptr) {
}

_bInt::_bigInt(char d, _bInt *p): 
    digit(d), prev(p), next(nullptr) {
}

_bInt::_bigInt(char d, _bInt *p, _bInt *n): 
    digit(d), prev(p), next(n) {
}

_bInt::~_bigInt() {
}

char _bInt::getDigit() {
    return digit;
}

void _bInt::setDigit(char d) {
    digit = d;
}

_bInt* _bInt::getPrev() {
    return prev;
}

void _bInt::setPrev(_bInt* p) {
    prev = p;
}

_bInt* _bInt::getNext() {
    return next;
}

void _bInt::setNext(_bInt* p) {
    next = p;
}

void swap(BigInt& first, BigInt& second) {
    std::swap(first.length, second.length);
    std::swap(first.isPositive, second.isPositive);
    std::swap(first.numHigh, second.numHigh);
    std::swap(first.numLow, second.numLow);
};


/*
 *  BigInt constructors/destructors
 */
BigInt::BigInt(): 
    numHigh(new _bInt()), numLow(numHigh), length(1), isPositive(true) {}

BigInt::BigInt(int n): 
    numHigh(new _bInt()), numLow(numHigh), length(1), isPositive(n >= 0) {
    if (n == 0)
        return;
    n = std::abs(n);
    length = std::floor(std::log10(n) + 1);
    char d = n % 10;
    n /= 10;
    numHigh->setDigit(d);
    for (int i = 0; i < length - 1; i++) {
        d = n % 10;
        n /= 10;
        numHigh->setPrev(new _bInt(d));
        _bInt *tmp = numHigh;
        numHigh = numHigh->getPrev();
        numHigh->setNext(tmp);
    }
}

BigInt::BigInt(const BigInt& n) {
    length = n.length;
    isPositive = n.isPositive;
    numHigh = new _bInt(n.numHigh->getDigit());
    numLow = numHigh;
    _bInt *p = n.numHigh;
    while(p->getNext() != nullptr) {
        numLow->setNext(new _bInt(p->getNext()->getDigit()));
        numLow->getNext()->setPrev(numLow);
        numLow = numLow->getNext();
        p = p->getNext();
    }
}

BigInt::~BigInt() {
    _bInt *p = numHigh;
    while (p->getNext() != nullptr) {
        p = p->getNext();
        delete p->getPrev();
    }
    delete p;
}



/*
 *  assignments and arithmetic operators
 */
BigInt& BigInt::operator=(const BigInt& n) {
    BigInt tmp(n);
    swap(*this, tmp);
    return *this;
}


BigInt& BigInt::operator=(int n) {
    BigInt tmp(n);
    swap(*this, tmp);
    return *this;
}

BigInt BigInt::operator+(const BigInt& n) {
    BigInt res(*this);
    _bInt *p1 = res.numLow, *p2 = n.numLow;
    char carry = 0;
    if (isPositive != n.isPositive) {
        res.isPositive = n.isPositive;
        res = res - n;
        res.isPositive = !res.isPositive;
        return res;
    }
    while (p2->getPrev() != nullptr) {
        carry = p1->getDigit() + p2->getDigit() + carry;
        p1->setDigit(carry % 10);
        carry /= 10;
        p2 = p2->getPrev();
        if (p1->getPrev() == nullptr) { 
            p1->setPrev(new _bInt(0, nullptr, p1));
            res.numHigh = p1->getPrev();
            res.length++;
        }
        p1 = p1->getPrev();
    }
    carry = p1->getDigit() + p2->getDigit() + carry;
    p1->setDigit(carry % 10);
    carry /= 10;
    if (p1->getPrev() == nullptr && p2->getPrev() == nullptr) {
        if (carry) {
            res.numHigh->setPrev(new _bInt(1));
            res.numHigh->getPrev()->setNext(res.numHigh);
            res.numHigh = res.numHigh->getPrev();
            res.length += 1;
        }
    } else if (p1->getPrev() != nullptr && p2->getPrev() == nullptr) {
        p1->getPrev()->setDigit(p1->getPrev()->getDigit() + carry);
        while(p1->getPrev() != nullptr && p1->getPrev()->getDigit() == 10) {
            p1 = p1->getPrev();
            if (p1->getPrev() == nullptr) {
                p1->setPrev(new _bInt(0, nullptr, p1));
                length++;
                res.numHigh = p1->getPrev();
            }
            p1->setDigit(0);
            p1->getPrev()->setDigit(p1->getPrev()->getDigit() + 1);
        }    
    }

    return res;
}

BigInt BigInt::operator-(const BigInt& n) {
    _bInt *p1, *p2;
    if (isPositive != n.isPositive) {
        BigInt res(*this);
        res.isPositive = n.isPositive;
        res = res + n;
        res.isPositive ^= !res.isPositive;
        return res;
    }
    bool lesser = (*this < n) ^ !isPositive;
    BigInt res;
    if (lesser) {
        res = n;
        p2 = numLow;
        res.isPositive = !isPositive; 
    } else {
        res = *this;
        p2 = n.numLow;
    }
    p1 = res.numLow;
    char carry = 0;
    while(p2 != nullptr) {
        char sub = p1->getDigit() - p2->getDigit() - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else 
            carry = 0;

        p1->setDigit(sub);
        p1 = p1 -> getPrev();
        p2 = p2 -> getPrev();
    }

    while (p1 != nullptr) {
        char sub = p1->getDigit() - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else 
            carry = 0;
        p1->setDigit(sub);
        p1 = p1 -> getPrev();
    }
    

    while (res.numHigh->getDigit() == 0 && res.length > 1) {
        _bInt *tmp = res.numHigh;
        res.numHigh = res.numHigh->getNext();
        delete tmp;
        res.numHigh->setPrev(nullptr);
        res.length--;
    }

    if (res.numHigh -> getDigit() == 0)
        res.isPositive = true;


    return res;
}

BigInt BigInt::operator+(int n) {
    return *this + BigInt(n);
}

BigInt BigInt::operator-(int n) {
    return *this - BigInt(n);
}

BigInt BigInt::operator-() {
    BigInt res(*this);
    res.isPositive = !isPositive;
    return res;
}

/*
 *  comparisons
 */
bool BigInt::operator==(const BigInt& n) const{
    return !(*this < n) && !(n < *this);
}

bool BigInt::operator!=(const BigInt& n) const{
    return (*this < n) || (n < *this);
}

bool BigInt::operator<(const BigInt& n) const {
    if (isPositive != n.isPositive)
        return !isPositive && n.isPositive;
    if (length != n.length)
        return ((length < n.length) && isPositive) 
            || ((length > n.length) && !isPositive);
    _bInt *p1 = numHigh, *p2 = n.numHigh;
    while (p1 != nullptr && p2 != nullptr) {
        char d1 = p1->getDigit(), d2 = p2->getDigit();
        if(d1 != d2)
            return ((d1 < d2) && isPositive) 
                || ((d1 > d2) && !isPositive);
        p1 = p1->getNext();
        p2 = p2->getNext();
    }
    return false;
}

bool BigInt::operator<=(const BigInt& n) const{
    return (*this < n) || (*this == n);
}

bool BigInt::operator>(const BigInt& n) const{
    return !(*this < n) && (*this != n);
}

bool BigInt::operator>=(const BigInt& n) const{
    return !(*this < n);
}

bool BigInt::operator==(int n) const{
    return *this == BigInt(n);
}

bool BigInt::operator!=(int n) const{
    return *this != BigInt(n);
}

bool BigInt::operator<(int n) const{
    return *this < BigInt(n);
}

bool BigInt::operator<=(int n) const{
    return *this <= BigInt(n);
}

bool BigInt::operator>(int n) const{
    return *this > BigInt(n);
}

bool BigInt::operator>=(int n) const{
    return *this >= BigInt(n);
}

/*
 *  _bigInt stream output
 */
std::ostream &operator<<(std::ostream &os, const BigInt &obj) {
    int len = obj.length + (obj.isPositive ? 0 : 1);
    std::string str(len, '-');
    _bInt *p = obj.numHigh; 
    int i = obj.isPositive ? 0 : 1;
    while(p->getNext() != nullptr) {
        str[i++] = '0' + p->getDigit();
        p = p->getNext();
    }
    str[len - 1] = '0' + p->getDigit();
    os << str;
    return os;
}

