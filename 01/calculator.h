#pragma once

#include <string>
#include "lexer.h"

class Calculator
{
public:
    Calculator();
    int calculate(std::string str);
private:
    int calc_sum();
    int calc_mul();
    int calc_atom();
    Lexer lexer;
    Lexeme lex;
};
