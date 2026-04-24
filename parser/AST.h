#pragma once
#include <memory>
#include <vector>
#include <string>

enum class NodeType {
    PROGRAM,
    VAR_DECL,
    PRINT,
    IF_STMT,
    NUMBER,
    IDENTIFIER,
    BINARY_OP
};

struct ASTNode {
    NodeType type;
    std::string value;

    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(NodeType t, const std::string& v = "")
        : type(t), value(v) {}
};