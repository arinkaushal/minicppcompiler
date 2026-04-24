#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

char Lexer::current() {
    if (pos >= input.size()) return '\0';
    return input[pos];
}

void Lexer::advance() { pos++; }

void Lexer::skipWhitespace() {
    while (isspace(current())) advance();
}

Token Lexer::identifier() {
    std::string result;
    while (isalnum(current())) {
        result += current();
        advance();
    }

    if (result == "int") return {TokenType::INT, result};
    if (result == "print") return {TokenType::PRINT, result};
    if (result == "if") return {TokenType::IF, result};
    if (result == "else") return {TokenType::ELSE, result};

    return {TokenType::IDENTIFIER, result};
}

Token Lexer::number() {
    std::string result;
    while (isdigit(current())) {
        result += current();
        advance();
    }
    return {TokenType::NUMBER, result};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (current() != '\0') {

        if (isspace(current())) {
            skipWhitespace();
            continue;
        }

        if (isalpha(current()))
            tokens.push_back(identifier());
        else if (isdigit(current()))
            tokens.push_back(number());
        else if (current() == '=') {
            tokens.push_back({TokenType::EQUALS, "="});
            advance();
        }
        else if (current() == '+') {
            tokens.push_back({TokenType::PLUS, "+"});
            advance();
        }
        else if (current() == '-') {
            tokens.push_back({TokenType::MINUS, "-"});
            advance();
        }
        else if (current() == '*') {
            tokens.push_back({TokenType::STAR, "*"});
            advance();
        }
        else if (current() == '/') {
            tokens.push_back({TokenType::SLASH, "/"});
            advance();
        }
        else if (current() == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            advance();
        }
        else if (current() == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            advance();
        }
        else if (current() == '>') {
            tokens.push_back({TokenType::GREATER, ">"});
            advance();
        }
        else if (current() == '<') {
            tokens.push_back({TokenType::LESS, "<"});
            advance();
        }
        else {
            advance();
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}