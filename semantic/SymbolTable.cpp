#include "SymbolTable.h"
#include <iostream>
#include <cstdlib>

void SymbolTable::declare(const std::string& name) {
    if (table.find(name) != table.end()) {
        std::cerr << "Error: Variable '" << name << "' already declared.\n";
        exit(1);
    }
    table.insert(name);
}

void SymbolTable::check(const std::string& name) {
    if (table.find(name) == table.end()) {
        std::cerr << "Error: Variable '" << name << "' not declared.\n";
        exit(1);
    }
}