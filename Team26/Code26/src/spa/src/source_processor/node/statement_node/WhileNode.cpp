#include "WhileNode.h"

WhileNode::WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> stmtListNode)
    : StmtNode(stmtIndex, StmtType::STMT_WHILE), condExprNode(condExprNode), stmtListNode(stmtListNode) {}


void WhileNode::evaluate(IStmtExtractor& extractor) {
}
