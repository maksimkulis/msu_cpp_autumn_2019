#include <stdexcept>
#include "calculator.h"
#include "lexer.h"

Calculator::Calculator() : lexer("")
{
}

int Calculator::calc_atom()
{
    int value = 1;
    if (lex.type == lex_type::MINUS) {
        value = -1;
        lex = lexer.get_next_lex();
    }
    if (lex.type == lex_type::NUM) {
        value *= lex.value;
        lex = lexer.get_next_lex();
    } else {
        throw std::runtime_error("Incorrect expression");
    }
    return value;
}

int Calculator::calc_mul()
{
    int atom = calc_atom();
    while (lex.type == lex_type::MUL ||
           lex.type == lex_type::DIV)
    {
        bool mul = true;
        if (lex.type == lex_type::DIV) {
            mul = false;
        }
        lex = lexer.get_next_lex();
        int second_atom = calc_atom();
        if (mul) {
            atom *= second_atom;
        } else {
            if (second_atom == 0) {
                throw std::runtime_error("Zero division");
            }
            atom /= second_atom;
        }
    }
    return atom;
}

int Calculator::calc_sum()
{
    int mul = calc_mul();
    while (lex.type == lex_type::PLUS ||
           lex.type == lex_type::MINUS)
    {
        int sign = 1;
        if (lex.type == lex_type::MINUS) {
            sign = -1;
        }
        lex = lexer.get_next_lex();
        mul += sign * calc_mul();
    }
    return mul;
}

int Calculator::calculate(const std::string& str)
{
    lexer = Lexer(str);
    lex = lexer.get_next_lex();
    int result = calc_sum();
    if (lex.type != lex_type::NULL_LEX) {
        throw std::runtime_error("Incorrect expression");
    }
    return result;
}
