#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include "Node.h"
#include "TermNode.h"

enum class ExprOperatorType {
    OPERATOR_ADD,
    OPERATOR_SUBTRACT
};

class ExprNode : public Node {
 public:
    std::shared_ptr<TermNode> term;
    std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams;
    ExprNode(std::shared_ptr<TermNode> term, std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams);
};
