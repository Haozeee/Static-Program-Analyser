#include "IfNode.h"

IfNode::IfNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> thenStmtListNode, std::shared_ptr<StmtListNode> elseStmtListNode)
    : StmtNode(stmtIndex, StmtType::STMT_IF), condExprNode(condExprNode), thenStmtListNode(thenStmtListNode),
    elseStmtListNode(elseStmtListNode) {}

void IfNode::evaluate(IStmtExtractor& extractor) {
}
