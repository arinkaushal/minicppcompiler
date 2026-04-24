#pragma once
#include "../parser/AST.h"

class CodeGen {
public:
    static void generate(std::shared_ptr<ASTNode> root);
};