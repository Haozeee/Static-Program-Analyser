#pragma once

#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include "Node.h"
#include "ExprNode.h"

#define REL_EXPR_OP_NUM 6

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

using RelExpr = std::tuple<RelExprOperatorType, std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>;

class CondExprNode : public Node {
 public:
     std::variant< std::shared_ptr<RelExpr>, std::pair<UnaryCondExprOperatorType, std::shared_ptr<CondExprNode>>,
         std::tuple<BinaryCondExprOperatorType, std::shared_ptr<CondExprNode>, std::shared_ptr<CondExprNode>>> params;

    CondExprNode(std::variant<std::shared_ptr<RelExpr>, std::pair<UnaryCondExprOperatorType,
        std::shared_ptr<CondExprNode>>, std::tuple<BinaryCondExprOperatorType, std::shared_ptr<CondExprNode>,
        std::shared_ptr<CondExprNode>>> params);
};
