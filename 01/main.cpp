#include <iostream>
#include <string>
#include "calculator.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " \"<expression>\"\n";
        return -1;
    }
    try {
        std::cout << Calculator().calculate(argv[1]) << std::endl;
    } catch (std::runtime_error & err) {
        std::cout << err.what() << std::endl;
        return -1;
    }
    return 0;
}
