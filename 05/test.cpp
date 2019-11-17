#include <iostream>
#include <cassert>
#include <sstream>

#include "Serializer.h"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    Data(uint64_t a, bool b, uint64_t c)
        : a(a)
        , b(b)
        , c(c)
    {
    }

    template <class S>
    Error serialize(S& serializer) const
    {
        return serializer(a, b, c);
    }
    template <class D>
    Error deserialize(D& deserializer)
    {
        Error error = Error::NoError;
        if ((error = deserializer.load(a)) != Error::NoError) {
            return error;
        }
        if ((error = deserializer.load(b)) != Error::NoError) {
            return error;
        }
        return deserializer.load(c);
    }
};

int main()
{
    Data x(1, true, 2);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    auto s2 = std::stringstream("");
    Deserializer d2(s2);
    assert (d2.load(y) == Error::CorruptedArchive);

    auto s3 = std::stringstream("1 privet 3");
    Deserializer d3(s3);
    assert (d3.load(y) == Error::CorruptedArchive);

    auto s4 = std::stringstream("1000 1");
    Deserializer d4(s4);
    assert (d4.load(y) == Error::CorruptedArchive);

    y = {0, true, 0};
    auto s5 = std::stringstream("100 false 500");
    Deserializer d5(s5);
    assert (d5.load(y) == Error::NoError);

    assert(y.a == 100);
    assert(y.b == false);
    assert(y.c == 500);
    return 0;
}
