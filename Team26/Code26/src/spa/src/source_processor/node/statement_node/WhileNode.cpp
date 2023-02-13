#include "WhileNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

WhileNode::WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> stmtListNode)
    : StmtNode(stmtIndex, StmtType::STMT_WHILE), condExprNode(condExprNode), stmtListNode(stmtListNode) {}


void WhileNode::evaluate(IStmtExtractor& extractor) {
    extractor.extractWhile(std::make_shared<WhileNode>(stmtIndex, condExprNode, stmtListNode));
}
