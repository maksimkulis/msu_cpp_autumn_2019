#pragma once
#include <exception>
#include <string>

// class LexerException : public Exeption
// {
// };

enum lex_type
{
    NULL_LEX,
    NUM,
    PLUS,
    MINUS,
    MUL,
    DIV
};

struct Lexeme
{
    Lexeme() : type(lex_type::NULL_LEX), value(0) {}
    lex_type type;
    int value;
};


class Lexer
{
public:
    Lexer(std::string str);
    Lexeme get_next_lex();
private:
    bool process_sym(char c);

    Lexeme lex;
    int value;
    bool read_digit;
    int str_ind;
    std::string str;
};
