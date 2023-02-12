#pragma once

#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>
#include "Node.h"
#include "ExprNode.h"

#define REL_EXPR_OP_NUM 6

enum class CondExprNodeType {
    RELEXPR,
    BINARYCONDEXPR,
    UNARYCONDEXPR
};

enum class RelExprOperatorType {
    GT,
    GTE,
    LT,
    LTE,
    EQ,
    NEQ
};

enum class BinaryCondOperatorType {
    AND,
    OR
};

enum class UnaryCondOperatorType {
    NOT
};

using RelExpr = std::tuple<RelExprOperatorType, std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>;

class CondExprNode : public Node {
 public:
    std::optional<std::shared_ptr<RelExpr>> relExpr;
    std::optional<std::tuple<UnaryCondOperatorType, std::shared_ptr<CondExprNode>>> unaryCondExpr;
    std::optional<std::tuple<BinaryCondOperatorType, std::shared_ptr<CondExprNode>, std::shared_ptr<CondExprNode>>> binaryCondExpr;
    std::string str;
    CondExprNodeType condExprNodeType;

    CondExprNode(std::shared_ptr<RelExpr> relExpr);
    CondExprNode(std::tuple<UnaryCondOperatorType, std::shared_ptr<CondExprNode>> unaryCondExpr, std::string str);
    CondExprNode(std::tuple<BinaryCondOperatorType, std::shared_ptr<CondExprNode>, std::shared_ptr<CondExprNode>> binaryCondExpr, std::string str);

    bool isRelExpr();
    bool isUnaryCondExpr();
    bool isBinaryCondExpr();
    std::optional<std::vector<std::shared_ptr<CondExprNode>>> returnNodes();
};
