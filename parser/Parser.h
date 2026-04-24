#pragma once
#include "../lexer/Token.h"
#include "../semantic/SymbolTable.h"
#include "AST.h"
#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<ASTNode> parseProgram();

private:
    std::vector<Token> tokens;
    size_t pos;
    SymbolTable symbols;

    Token current();
    void advance();

    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseComparison();   // ADD THIS
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
    std::shared_ptr<ASTNode> parseIf();
};