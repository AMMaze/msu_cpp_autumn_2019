#include "src/serializer.h"
#include "src/deserializer.h"
#include "src/data.h"
#include <iostream>
#include <sstream>
#include <cassert>

int main() {

    Data x { 1, true, 2 };

    std::stringstream ss;

    Serializer serializer(ss);
    serializer.save(x);


    Data y { 0, false, 0 };

    Deserializer deserializer(ss);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    
    return 0;
}
