#include "ExprNode.h"

ExprNode::ExprNode(std::shared_ptr<BinaryOpNode> binaryOpNode) {
    if (std::get<0>(*binaryOpNode) == OperatorType::ADD || std::get<0>(*binaryOpNode) == OperatorType::SUBTRACT) {
        exprNodeType = ExprNodeType::EXPR;
    } else {
        exprNodeType = ExprNodeType::TERM;
    }
    this->binaryOpNode = binaryOpNode;

    OperatorType opType = std::get<0>(*binaryOpNode);
    ExprNode exprNode1 = *(std::get<1>(*binaryOpNode));
    ExprNode exprNode2 = *(std::get<2>(*binaryOpNode));

    this->str = exprNode1.str;
    if (opType == OperatorType::MULTIPLY) {
        this->str += "*";
    } else if (opType == OperatorType::DIVIDE) {
        this->str += "/";
    } else if (opType == OperatorType::MOD) {
        this->str += "%";
    } else if (opType == OperatorType::ADD) {
        this->str += "+";
    } else {
        this->str += "-";
    }
    this->str += exprNode2.str;
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
