#include "ExprNode.h"

ExprNode::ExprNode(std::shared_ptr<TermNode> term, std::optional<std::pair<ExprOperatorType,
    std::shared_ptr<ExprNode>>> optionalParams)
    : term(term), optionalParams(optionalParams) {}
