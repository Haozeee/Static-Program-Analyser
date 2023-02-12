#include "CondExprNode.h"


CondExprNode::CondExprNode(std::shared_ptr<RelExpr> relExpr) {
    this->relExpr = relExpr;
    condExprNodeType = CondExprNodeType::RELEXPR;

    RelExpr r = *relExpr;
    RelExprOperatorType opType = std::get<0>(r);
    ExprNode exprnode1 = *std::get<1>(r);
    ExprNode exprnode2 = *std::get<2>(r);

    this->str = exprnode1.str;
    if (opType == RelExprOperatorType::EQ) {
        this->str += "==";
    } else if (opType == RelExprOperatorType::NEQ) {
        this->str += "!=";
    } else if (opType == RelExprOperatorType::LT) {
        this->str += "<";
    } else if (opType == RelExprOperatorType::LTE) {
        this->str += "<=";
    } else if (opType == RelExprOperatorType::GT) {
        this->str += ">";
    } else {
        this->str += ">=";
    }
    this->str += exprnode2.str;
}

CondExprNode::CondExprNode(std::tuple<UnaryCondOperatorType, std::shared_ptr<CondExprNode>> unaryCondExpr) {
    this->unaryCondExpr = unaryCondExpr;
    condExprNodeType = CondExprNodeType::UNARYCONDEXPR;

    CondExprNode condExprNode = *std::get<1>(unaryCondExpr);
    this->str = "!(" + condExprNode.str +")";
}

CondExprNode::CondExprNode(std::tuple<BinaryCondOperatorType, std::shared_ptr<CondExprNode>,
    std::shared_ptr<CondExprNode>> binaryCondExpr) {
    this->binaryCondExpr = binaryCondExpr;
    condExprNodeType = CondExprNodeType::BINARYCONDEXPR;

    CondExprNode condExprNode1 = *std::get<1>(binaryCondExpr);
    CondExprNode condExprNode2 = *std::get<2>(binaryCondExpr);
    BinaryCondOperatorType opType = std::get<0>(binaryCondExpr);

    this->str = "(" + condExprNode1.str;
    if (opType ==BinaryCondOperatorType::AND) {
        this->str += ")&&(";
    } else {
        this->str += ")||(";
    }
    this->str += condExprNode2.str + ")";
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
