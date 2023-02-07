#include "CondExprNode.h"

CondExprNode::CondExprNode(std::variant<RelExpr, std::pair<UnaryCondExprOperatorType, CondExprNode*>,
    std::tuple<CondExprNode*, BinaryCondExprOperatorType, CondExprNode*>> params)
    : params(params) {}
