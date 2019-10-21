#include <cctype>
#include <iostream>
#include <stdexcept>
#include "lexer.h"

Lexer::Lexer(const std::string& str)
    : str(str)
    , str_ind(0)
    , read_digit(false)
    , value(0)
{
}

bool Lexer::process_sym(char c)
{
    switch(read_digit) {
    case false:
        switch(c) {
        case '+':
            lex.type = lex_type::PLUS;
            return true;
        case '-':
            lex.type = lex_type::MINUS;
            return true;
        case '*':
            lex.type = lex_type::MUL;
            return true;
        case '/':
            lex.type = lex_type::DIV;
            return true;
        case '\0':
            lex.type = lex_type::NULL_LEX;
            return true;
        default:
            if (std::isdigit(c)) {
                read_digit = true;
                value = c - '0';
                lex.type = lex_type::NUM;
                return false;
            } else if (std::isspace(c)) {
                return false;
            } else {
                throw std::runtime_error("Unexpected symbol");
            }
        }
    case true:
        switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '\0':
            lex.value = value;
            read_digit = false;
            str_ind--;
            return true;
        default:
            if (std::isdigit(c)) {
                value = 10 * value + (c - '0');
                return false;
            } else if (std::isspace(c)) {
                lex.value = value;
                read_digit = false;
                str_ind--;
                return true;
            } else {
                throw std::runtime_error("Unexpected symbol");
            }
        }
    }
}

Lexeme Lexer::get_next_lex()
{
    while (str_ind <= str.size()) {
        if (process_sym(str[str_ind++])) {
            break;
        }
    }
    return lex;
}
