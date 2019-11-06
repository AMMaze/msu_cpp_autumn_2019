#include "bigint.h"
#include <cmath>
#include <stdlib.h> 
#include <string>

using _bInt = BigInt::_bigInt;

/*
 *  _bigInt constructors/destructors
 */
_bInt::_bigInt(): 
    digit(new char()), prev(nullptr), next(nullptr) {
    *digit = 0;
}

_bInt::_bigInt(char d): 
    digit(new char()), prev(nullptr), next(nullptr) {
    *digit = d;
}

_bInt::_bigInt(char d, _bInt *p): 
    digit(new char()), prev(p), next(nullptr) {
    *digit = d;
}

_bInt::_bigInt(char d, _bInt *p, _bInt *n): 
    digit(new char()), prev(p), next(n) {
    *digit = d;
}

_bInt::~_bigInt() {
    delete digit;
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
    *(numHigh->digit) = d;
    for (int i = 0; i < length - 1; i++) {
        d = n % 10;
        n /= 10;
        numHigh->prev = new _bInt(d);
        _bInt *tmp = numHigh;
        numHigh = numHigh->prev;
        numHigh->next = tmp;
    }
}

BigInt::BigInt(const BigInt& n) {
    length = n.length;
    isPositive = n.isPositive;
    numHigh = new _bInt(*(n.numHigh->digit));
    numLow = numHigh;
    _bInt *p = n.numHigh;
    while(p->next != nullptr) {
        numLow->next = new _bInt(*(p->next->digit));
        numLow->next->prev = numLow;
        numLow = numLow->next;
        p = p->next;
    }
}

BigInt::~BigInt() {
    _bInt *p = numHigh;
    while (p->next != nullptr) {
        p = p->next;
        delete p->prev;
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
    while (p2->prev != nullptr) {
        carry = *(p1->digit) + *(p2->digit) + carry;
        *(p1->digit) = carry % 10;
         carry /= 10;
        p2 = p2->prev;
        if (p1->prev == nullptr) { 
            p1->prev = new _bInt(0, nullptr, p1);
            res.numHigh = p1->prev;
            res.length++;
        }
        p1 = p1->prev;
    }
    carry = *(p1->digit) + *(p2->digit) + carry;
    *(p1->digit) = carry % 10;
    carry /= 10;
    if (p1->prev == nullptr && p2->prev == nullptr) {
        if (carry) {
            res.numHigh->prev = new _bInt(1);
            res.numHigh->prev->next = res.numHigh;
            res.numHigh = res.numHigh->prev;
            res.length += 1;
        }
    } else if (p1->prev != nullptr && p2->prev == nullptr) {
        *(p1->prev->digit) += carry;
        while(p1->prev != nullptr && *(p1->prev->digit) == 10) {
            p1 = p1->prev;
            if (p1->prev == nullptr) {
                p1->prev = new _bInt(0, nullptr, p1);
                length++;
                res.numHigh = p1->prev;
            }
            *(p1->digit) = 0;
            *(p1->prev->digit) += 1;
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
        char sub = *p1->digit - *p2->digit - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else 
            carry = 0;

        *p1->digit = sub;
        p1 = p1 -> prev;
        p2 = p2 -> prev;
    }

    while (p1 != nullptr) {
        char sub = *p1->digit - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else 
            carry = 0;
        *p1->digit = sub;
        p1 = p1 -> prev;
    }
    

    while (*res.numHigh->digit == 0 && res.length > 1) {
        _bInt *tmp = res.numHigh;
        res.numHigh = res.numHigh->next;
        delete tmp;
        res.numHigh->prev = nullptr;
        res.length--;
    }

    if (*res.numHigh -> digit == 0)
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
        char d1 = *p1->digit, d2 = *p2->digit;
        if(d1 != d2)
            return ((d1 < d2) && isPositive) 
                || ((d1 > d2) && !isPositive);
        p1 = p1->next;
        p2 = p2->next;
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
    while(p->next != nullptr) {
        str[i++] = '0' + *(p->digit);
        p = p->next;
    }
    str[len - 1] = '0' + *(p->digit);
    os << str;
    return os;
}

