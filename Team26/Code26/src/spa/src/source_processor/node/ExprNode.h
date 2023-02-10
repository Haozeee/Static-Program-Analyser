#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include "Node.h"
//#include "TermNode.h"

enum class TermOperatorType {
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    OPERATOR_MOD
};

enum class ExprOperatorType {
    OPERATOR_ADD,
    OPERATOR_SUBTRACT
};

using Factor = std::variant<std::string, int>;
//using Term = std::pair<std::shared_ptr<Factor>, std::optional<std::pair<TermOperatorType, std::shared_ptr<ExprNode>>>>;
class ExprNode : public Node {
public:
    std::pair<std::variant<std::shared_ptr<Factor>, std::shared_ptr<ExprNode>>, std::optional<std::pair<TermOperatorType, std::shared_ptr<ExprNode>>>> term;
    std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams;

    ExprNode(std::pair<std::variant<std::shared_ptr<Factor>, std::shared_ptr<ExprNode>>, std::optional<std::pair<TermOperatorType,
        std::shared_ptr<ExprNode>>>> term, std::optional<std::pair<ExprOperatorType, std::shared_ptr<ExprNode>>> optionalParams);
};
