#include "CodeGen.h"
#include <fstream>

void genExpr(std::ofstream& out, std::shared_ptr<ASTNode> node) {

    if (node->type == NodeType::NUMBER ||
        node->type == NodeType::IDENTIFIER) {

        out << node->value;
    }

    else if (node->type == NodeType::BINARY_OP) {

        out << "(";
        genExpr(out, node->left);
        out << " " << node->value << " ";
        genExpr(out, node->right);
        out << ")";
    }
}

void CodeGen::generate(std::shared_ptr<ASTNode> root) {

    std::ofstream out("output/output.cpp");

    out << "#include <iostream>\n";
    out << "using namespace std;\n\n";
    out << "int main() {\n";

    for (auto stmt : root->children) {

        if (stmt->type == NodeType::VAR_DECL) {

            out << "    int " << stmt->value << " = ";
            genExpr(out, stmt->left);
            out << ";\n";
        }

        else if (stmt->type == NodeType::PRINT) {

            out << "    cout << ";
            genExpr(out, stmt->left);
            out << " << endl;\n";
        }

        else if (stmt->type == NodeType::IF_STMT) {

            out << "    if (";
            genExpr(out, stmt->left);
            out << ") {\n";

            auto thenStmt = stmt->children[0];

            if (thenStmt && thenStmt->type == NodeType::PRINT) {
                out << "        cout << ";
                genExpr(out, thenStmt->left);
                out << " << endl;\n";
            }

            out << "    }";

            if (stmt->children.size() > 1 && stmt->children[1] != nullptr) {

                out << " else {\n";

                auto elseStmt = stmt->children[1];

                if (elseStmt && elseStmt->type == NodeType::PRINT) {
                    out << "        cout << ";
                    genExpr(out, elseStmt->left);
                    out << " << endl;\n";
                }

                out << "    }";
            }

            out << "\n";
        }
    }

    out << "    return 0;\n";
    out << "}\n";
}