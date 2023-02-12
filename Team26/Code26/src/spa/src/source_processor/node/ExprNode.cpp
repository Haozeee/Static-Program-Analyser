#include "ExprNode.h"

ExprNode::ExprNode(std::shared_ptr<BinaryOpNode> binaryOpNode, std::string str) {
    if (std::get<0>(*binaryOpNode) == OperatorType::ADD || std::get<0>(*binaryOpNode) == OperatorType::SUBTRACT) {
        exprNodeType = ExprNodeType::EXPR;
    } else {
        exprNodeType = ExprNodeType::TERM;
    }
    this->binaryOpNode = binaryOpNode;
    this->str = str;
}

ExprNode::ExprNode(int constant) {
    this->constant = constant;
    exprNodeType = ExprNodeType::FACTOR_CONSTANT;
    this->str = constant;
}

ExprNode::ExprNode(std::string varName) {
    this->varName = varName;
    exprNodeType = ExprNodeType::FACTOR_VARIABLE;
    this->str = varName;
}

bool ExprNode::isConstant() {
    return exprNodeType == ExprNodeType::FACTOR_CONSTANT;
}

bool ExprNode::isVariable() {
    return exprNodeType == ExprNodeType::FACTOR_VARIABLE;
}

std::optional<std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>>> ExprNode::returnNodes() {
    if (!binaryOpNode.has_value()) {
        return std::nullopt;
    }

    BinaryOpNode b = *binaryOpNode.value();
    return std::make_pair(std::get<1>(b), std::get<2>(b));
}
