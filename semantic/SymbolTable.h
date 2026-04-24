#pragma once
#include <unordered_set>
#include <string>

class SymbolTable {
public:
    void declare(const std::string& name);
    void check(const std::string& name);

private:
    std::unordered_set<std::string> table;
};