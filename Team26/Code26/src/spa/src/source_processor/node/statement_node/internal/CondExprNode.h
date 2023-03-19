#pragma once
#include <unordered_set>
#include <string>

class CondExprNode {
 public:
    const std::unordered_set<std::string> exprVariables;
    const std::unordered_set<int> exprConstants;

    CondExprNode(std::unordered_set<std::string> exprVariables,
                 std::unordered_set<int> exprConstants);
};
