#include <iostream>
#include <cstring> //strcmp
#include <cassert> //assert

#include "format.h"

#define check_err(str, ...) {err = false; try {format(str, __VA_ARGS__);} catch(std::runtime_error) {err = true;} assert(err);}
int main()
{
    assert(!format("{1}opa chirik {0} {1}", 5, 10).compare("10opa chirik 5 10"));
    assert(!format("{0}{1}{2}{4}", false, true, 2, 3, "444").compare("012444"));
    assert(!format("pornhub.com").compare("pornhub.com"));
    assert(!format("{0}", "{0}").compare("{0}"));
    bool err = false;
    check_err("ras dva{4r}", 5);
    check_err("Chill bez krinja{}", 0);
    check_err("okay boomer}", 2);
    check_err("{0}{5}{1}", 1, "lel");
    check_err("{{0}}", 1);
    check_err("Big brother is watching {0", "you");

    return 0;
}
