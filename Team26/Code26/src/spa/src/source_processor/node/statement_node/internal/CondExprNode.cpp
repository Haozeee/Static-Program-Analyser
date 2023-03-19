#include "CondExprNode.h"

CondExprNode::CondExprNode(std::unordered_set<std::string> exprVariables, std::unordered_set<int> exprConstants) :
exprVariables(std::move(exprVariables)), exprConstants(std::move(exprConstants))  {
}
