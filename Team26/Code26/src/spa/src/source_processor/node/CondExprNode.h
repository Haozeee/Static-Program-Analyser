#pragma once

#include <optional>
#include <string>
#include <utility>
#include <variant>
#include "Node.h"
#include "ExprNode.h"

enum class RelExprOperatorType {
    OPERATOR_GT,
    OPERATOR_GTE,
    OPERATOR_LT,
    OPERATOR_LTE,
    OPERATOR_EQ,
    OPERATOR_NEQ
};

enum class BinaryCondExprOperatorType {
    OPERATOR_AND,
    OPERATOR_OR
};

enum class UnaryCondExprOperatorType {
    OPERATOR_NOT
};

using RelFactor = std::variant<std::string, int, ExprNode*>;
using RelExpr = std::tuple<RelExprOperatorType, RelFactor, RelFactor>;

class CondExprNode : public Node {
 public:
     std::variant<RelExpr, std::pair<UnaryCondExprOperatorType, CondExprNode*>,
         std::tuple<CondExprNode*, BinaryCondExprOperatorType, CondExprNode*>> params;

    CondExprNode(std::variant<RelExpr, std::pair<UnaryCondExprOperatorType, CondExprNode*>,
        std::tuple<CondExprNode*, BinaryCondExprOperatorType, CondExprNode*>> params);
};
