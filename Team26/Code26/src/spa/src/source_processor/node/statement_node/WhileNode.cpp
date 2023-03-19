#include "WhileNode.h"
#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

WhileNode::WhileNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> stmtListNode) :
    StmtNode(stmtIndex, StmtType::STMT_WHILE),
    condExprNode(std::move(condExprNode)),
    stmtListNode(std::move(stmtListNode)) {}


void WhileNode::evaluate(IStmtExtractor& extractor) {
    extractor.extractWhile(this->shared_from_this());
}

