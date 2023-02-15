#pragma once

#include <memory>
#include <optional>
#include <string>
#include <tuple>
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
    ExprNode(std::string factor, ExprNodeType exprNodeType);
    ExprNode(std::shared_ptr<BinaryOpNode> binaryOpNode, std::string str);

    bool isConstant();
    bool isVariable();
    std::optional<int> getConstant();
    std::optional<std::string> getVariable();
    std::string getRawString();

    std::optional<std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>> returnNodes();

 private:
    std::optional<int> constant;
    std::optional<std::string> varName;
    std::optional<std::shared_ptr<BinaryOpNode>> binaryOpNode;
    std::string str;
    ExprNodeType exprNodeType;
};
