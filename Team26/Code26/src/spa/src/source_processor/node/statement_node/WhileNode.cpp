#include "WhileNode.h"

WhileNode::WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> stmtListNode)
    : StmtNode(stmtIndex), condExprNode(condExprNode), stmtListNode(stmtListNode) {}


void WhileNode::evaluate(AbstractExtractor& extractor) {
    // TODO
}
