#include "ExprNode.h"

ExprNode::ExprNode(std::pair<std::variant<std::shared_ptr<Factor>, std::shared_ptr<ExprNode>>,
    std::optional<std::pair<TermOperatorType, std::shared_ptr<ExprNode>>>> term,
    std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams)
    : term(term), optionalParams(optionalParams) {}
