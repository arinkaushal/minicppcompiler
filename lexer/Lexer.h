#pragma once
#include "Token.h"
#include <vector>

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;

    char current();
    void advance();
    void skipWhitespace();
    Token identifier();
    Token number();
};