#include "bigint.h"
#include <cmath>
#include <stdlib.h> 
#include <string>

using _bInt = BigInt::_bigInt;

/*
 *  _bigInt constructors/destructors
 */
_bInt::_bigInt(): 
    digit(new char()), prev(nullptr), next(nullptr) {}

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
    //numLow = new _bInt(d);
    //numHigh = numLow;
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
