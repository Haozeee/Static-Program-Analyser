#pragma once

#include <optional>
#include <string>
#include <utility>
#include <variant>
#include "Node.h"

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

typedef struct Term {
    Factor factor;
    std::optional<std::pair<TermOperatorType, struct Term*>> optionalParams;
} Term;

class ExprNode : public Node {
 public:
    Term term;
    std::optional<std::pair<ExprOperatorType, ExprNode*>> optionalParams;
    explicit ExprNode(Term term, std::optional<std::pair<ExprOperatorType, ExprNode*>> optionalParams);
};
