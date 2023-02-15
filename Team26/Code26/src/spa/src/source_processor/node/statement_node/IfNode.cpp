#include "IfNode.h"

#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"
#include "source_processor/design_extractor/interface/IPatternExtractor.h"

IfNode::IfNode(int stmtIndex, std::shared_ptr<CondExprNode> condExprNode,
    std::shared_ptr<StmtListNode> thenStmtListNode, std::shared_ptr<StmtListNode> elseStmtListNode)
    : StmtNode(stmtIndex, StmtType::STMT_IF),
    condExprNode(std::move(condExprNode)),
    thenStmtListNode(std::move(thenStmtListNode)),
    elseStmtListNode(std::move(elseStmtListNode)) {}

void IfNode::evaluate(IStmtExtractor& extractor) {
    extractor.extractIf(this->shared_from_this());
}

void IfNode::evaluatePattern(IPatternExtractor &extractor) {
    extractor.extractIf(this->shared_from_this());
}
