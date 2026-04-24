#pragma once
#include <string>

enum class TokenType {
    INT,
    PRINT,
    IF,
    ELSE,
    IDENTIFIER,
    NUMBER,
    EQUALS,
    PLUS,      
    MINUS,     
    STAR,      
    SLASH,
    GREATER,
    LESS,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    std::string value;
};