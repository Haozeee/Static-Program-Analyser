#include "ExprNode.h"

ExprNode::ExprNode(Term term, std::optional<std::pair<ExprOperatorType, ExprNode*>> optionalParams)
    : term(term), optionalParams(optionalParams) {}
