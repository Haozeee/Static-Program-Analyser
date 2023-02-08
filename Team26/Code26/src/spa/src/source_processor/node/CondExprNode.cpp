#include "CondExprNode.h"

CondExprNode::CondExprNode(std::variant<std::shared_ptr<RelExpr>, std::pair<UnaryCondExprOperatorType, 
    std::shared_ptr<CondExprNode>>, std::tuple<BinaryCondExprOperatorType, std::shared_ptr<CondExprNode>,
    std::shared_ptr<CondExprNode>>> params)
    : params(params) {}
