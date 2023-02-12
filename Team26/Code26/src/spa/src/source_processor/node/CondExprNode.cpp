#include "CondExprNode.h"


CondExprNode::CondExprNode(std::shared_ptr<RelExpr> relExpr, std::string str) {
    this->relExpr = relExpr;
    condExprNodeType = CondExprNodeType::RELEXPR;
    this->str = str;
}

CondExprNode::CondExprNode(std::tuple<UnaryCondOperatorType, std::shared_ptr<CondExprNode>> unaryCondExpr
    , std::string str) {
    this->unaryCondExpr = unaryCondExpr;
    condExprNodeType = CondExprNodeType::UNARYCONDEXPR;
    this->str = str;
}

CondExprNode::CondExprNode(std::tuple<BinaryCondOperatorType, std::shared_ptr<CondExprNode>,
    std::shared_ptr<CondExprNode>> binaryCondExpr, std::string str) {
    this->binaryCondExpr = binaryCondExpr;
    condExprNodeType = CondExprNodeType::BINARYCONDEXPR;
    this->str = str;
}

bool CondExprNode::isRelExpr() {
    return condExprNodeType == CondExprNodeType::RELEXPR;
}

bool CondExprNode::isUnaryCondExpr() {
    return condExprNodeType == CondExprNodeType::UNARYCONDEXPR;
}

bool CondExprNode::isBinaryCondExpr() {
    return condExprNodeType == CondExprNodeType::BINARYCONDEXPR;
}

std::optional<std::vector<std::shared_ptr<CondExprNode>>> CondExprNode::returnNodes() {
    if (condExprNodeType == CondExprNodeType::RELEXPR) {
        return std::nullopt;
    } else if (condExprNodeType == CondExprNodeType::UNARYCONDEXPR) {
        std::vector<std::shared_ptr<CondExprNode>> nodes;
        nodes.emplace_back(std::get<1>(unaryCondExpr.value()));
        return nodes;
    }

    std::vector<std::shared_ptr<CondExprNode>> nodes;
    nodes.emplace_back(std::get<1>(binaryCondExpr.value()));
    nodes.emplace_back(std::get<2>(binaryCondExpr.value()));
    return nodes;
}
