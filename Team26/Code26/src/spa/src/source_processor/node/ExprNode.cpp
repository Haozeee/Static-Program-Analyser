#include "ExprNode.h"

ExprNode::ExprNode(std::pair<std::variant<std::shared_ptr<Factor>, std::shared_ptr<ExprNode>>,
    std::optional<std::pair<TermOperatorType, std::shared_ptr<ExprNode>>>> term_,
    std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams_) {
    term = term_;
    optionalParams = optionalParams_;
    exprNodeType = ExprNodeType::EXPR;
    if (std::holds_alternative<std::shared_ptr<ExprNode>>(term.first)) {
        exprNodeType = ExprNodeType::TERM;
    } else if (std::holds_alternative<std::shared_ptr<Factor>>(term.first)) {
        exprNodeType = ExprNodeType::FACTOR;
    }
}
