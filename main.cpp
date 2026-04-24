#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "codegen/CodeGen.h"
#include <fstream>
#include <sstream>
#include <iostream>

int main() {

    std::ifstream file("examples/test.as");
    if (!file) {
        std::cout << "File not found\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto ast = parser.parseProgram();

    CodeGen::generate(ast);

    std::cout << "C++ generated in output/output.cpp\n";
    std::cout << "Compiling...\n";

    system("g++ output/output.cpp -o output/output.exe");

    std::cout << "Running...\n";
    system(".\\output\\output.exe");

    return 0;
}