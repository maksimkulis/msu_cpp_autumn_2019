#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cassert>

#include "BigInt.h"

#define str_test(given, expected) {\
    std::stringstream out; \
    out << (given); \
    if(out.str() != (expected)) \
        std::cout << "Test on line " << __LINE__ << " failed\n"; \
}
#define test(given, expected) {\
    if ((given) != (expected)) \
        std::cout << "Test on line " << __LINE__ << " failed\n"; \
}

int main()
{
    BigInt value10 = 10;
    str_test(value10, "10");
    auto value10_2 = value10;
    str_test(value10_2, "10");
    auto value11 = value10 + 1;
    str_test(value11, "11");
    BigInt value10_3;
    value10_3 = value10;
    str_test(value10_3, "10");
    value10_3 = value10 + 1;
    str_test(value10_3, "11");
    BigInt valuem5 = -5;
    str_test(valuem5, "-5");
    BigInt valuem10 = -10;
    str_test(valuem10 - valuem5, "-5");

    test(value10 == value10_2, true);
    test(value10 == valuem10, false);
    test(value10 == value11, false);
    test(value10 != value11, true);
    test(value10 != value10_2, false);
    test(value11 <= value11, true);
    test(valuem10 <= value10, true);
    test(value10 <= value11, true);
    test(value10 >= value11, false);
    test(valuem5 >= valuem10, true);
    test(value11 >= value11, true);
    test(value11 >= value10, true);
    test(value11 < value10, false);
    test(value11 < value11, false);
    test(value10 < value11, true);
    test(value10 > value11, false);
    test(value11 > value11, false);
    test(value11 > value10, true);


    BigInt value2pow999 = 1;
    BigInt value2pow1000;
    for (int i = 1; i <= 999; i++) {
        value2pow999 = value2pow999 + value2pow999;
    }
    value2pow1000 = value2pow999 + value2pow999;
    str_test(value2pow1000, "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376");
    str_test((value2pow999 - 123456789) + (value2pow999 - 123456789), "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205421155798");
    test(value2pow1000 - value2pow999 == value2pow999, true);
    test(value2pow999 == value2pow1000, false);
    test(value2pow1000 >= value2pow999, true);
    test(value2pow1000 < value2pow999, false);
    return 0;
}
