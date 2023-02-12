#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include "Node.h"

enum class ExprNodeType {
    EXPR,
    TERM,
    FACTOR_CONSTANT,
    FACTOR_VARIABLE
};

enum class OperatorType {
    MULTIPLY,
    DIVIDE,
    MOD,
    ADD,
    SUBTRACT
};

class ExprNode;

class ExprNode : public Node {
 public:
    using BinaryOpNode = std::tuple<OperatorType, std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>;

    std::optional<int> constant;
    std::optional<std::string> varName;
    std::optional<std::shared_ptr<BinaryOpNode>> binaryOpNode;
    std::string str;
    ExprNodeType exprNodeType;


    ExprNode(int constant);
    ExprNode(std::string varName);
    ExprNode(std::shared_ptr<BinaryOpNode> binaryOpNode, std::string str);

    bool isConstant();
    bool isVariable();
    std::optional<std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>> returnNodes();
};
