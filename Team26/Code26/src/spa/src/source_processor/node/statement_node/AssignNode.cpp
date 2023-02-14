#include "AssignNode.h"

#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"
#include "source_processor/design_extractor/interface/IPatternExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode)
    : StmtNode(stmtIndex, StmtType::STMT_ASSIGN), varName(std::move(varName)), exprNode(std::move(exprNode)) {}

void AssignNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractAssign(shared_from_this());
}

void AssignNode::evaluatePattern(IPatternExtractor &extractor) {
    extractor.extractAssign(shared_from_this());
}
