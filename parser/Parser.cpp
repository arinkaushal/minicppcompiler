#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), pos(0) {}

Token Parser::current() {
    return tokens[pos];
}

void Parser::advance() {
    if (pos < tokens.size())
        pos++;
}

/////////////////////////////////////////////////////
// FACTOR  → number | identifier | (expression)
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseFactor() {

    if (current().type == TokenType::NUMBER) {
        auto node = std::make_shared<ASTNode>(NodeType::NUMBER, current().value);
        advance();
        return node;
    }

    if (current().type == TokenType::IDENTIFIER) {
        symbols.check(current().value);
        auto node = std::make_shared<ASTNode>(NodeType::IDENTIFIER, current().value);
        advance();
        return node;
    }

    if (current().type == TokenType::LPAREN) {
        advance(); // (
        auto node = parseComparison();
        if (current().type != TokenType::RPAREN)
            throw std::runtime_error("Expected ')'");
        advance(); // )
        return node;
    }

    throw std::runtime_error("Invalid expression");
}

/////////////////////////////////////////////////////
// TERM → handles * and /
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseTerm() {

    auto left = parseFactor();

    while (current().type == TokenType::STAR ||
           current().type == TokenType::SLASH) {

        std::string op = current().value;
        advance();

        auto right = parseFactor();

        auto node = std::make_shared<ASTNode>(NodeType::BINARY_OP, op);
        node->left = left;
        node->right = right;

        left = node; // LEFT associative
    }

    return left;
}

/////////////////////////////////////////////////////
// EXPRESSION → handles + and -
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseExpression() {

    auto left = parseTerm();

    while (current().type == TokenType::PLUS ||
           current().type == TokenType::MINUS) {

        std::string op = current().value;
        advance();

        auto right = parseTerm();

        auto node = std::make_shared<ASTNode>(NodeType::BINARY_OP, op);
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

/////////////////////////////////////////////////////
// COMPARISON → handles > and <
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseComparison() {

    auto left = parseExpression();

    while (current().type == TokenType::GREATER ||
           current().type == TokenType::LESS) {

        std::string op = current().value;
        advance();

        auto right = parseExpression();

        auto node = std::make_shared<ASTNode>(NodeType::BINARY_OP, op);
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

/////////////////////////////////////////////////////
// STATEMENTS
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseStatement() {

    //////////////////////////////////////
    // int variable declaration
    //////////////////////////////////////
    if (current().type == TokenType::INT) {

        advance(); // int

        if (current().type != TokenType::IDENTIFIER)
            throw std::runtime_error("Expected variable name");

        std::string name = current().value;
        symbols.declare(name);
        advance();

        if (current().type != TokenType::EQUALS)
            throw std::runtime_error("Expected '='");

        advance();

        auto expr = parseComparison();

        auto node = std::make_shared<ASTNode>(NodeType::VAR_DECL, name);
        node->left = expr;

        return node;
    }

    //////////////////////////////////////
    // print(expression)
    //////////////////////////////////////
    if (current().type == TokenType::PRINT) {

        advance(); // print

        if (current().type != TokenType::LPAREN)
            throw std::runtime_error("Expected '('");

        advance();

        auto expr = parseComparison();

        if (current().type != TokenType::RPAREN)
            throw std::runtime_error("Expected ')'");

        advance();

        auto node = std::make_shared<ASTNode>(NodeType::PRINT);
        node->left = expr;

        return node;
    }

    //////////////////////////////////////
    // if statement
    //////////////////////////////////////
    if (current().type == TokenType::IF)
        return parseIf();

    throw std::runtime_error("Invalid statement");
}

/////////////////////////////////////////////////////
// IF STATEMENT
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseIf() {

    advance(); // if

    if (current().type != TokenType::LPAREN)
        throw std::runtime_error("Expected '(' after if");

    advance();

    auto condition = parseComparison();

    if (current().type != TokenType::RPAREN)
        throw std::runtime_error("Expected ')' after condition");

    advance();

    auto thenStmt = parseStatement();

    std::shared_ptr<ASTNode> elseStmt = nullptr;

    if (current().type == TokenType::ELSE) {
        advance();
        elseStmt = parseStatement();
    }

    auto node = std::make_shared<ASTNode>(NodeType::IF_STMT);
    node->left = condition;
    node->children.push_back(thenStmt);
    if (elseStmt)
    node->children.push_back(elseStmt);

    return node;
}

/////////////////////////////////////////////////////
// PROGRAM ROOT
/////////////////////////////////////////////////////

std::shared_ptr<ASTNode> Parser::parseProgram() {

    auto root = std::make_shared<ASTNode>(NodeType::PROGRAM);

    while (current().type != TokenType::END) {
        root->children.push_back(parseStatement());
    }

    return root;
}