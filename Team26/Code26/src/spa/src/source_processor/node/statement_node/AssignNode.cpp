#include "AssignNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"
#include "source_processor/design_extractor/interface/IPatternExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode)
    : StmtNode(stmtIndex, StmtType::STMT_ASSIGN), varName(varName), exprNode(exprNode) {}

void AssignNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractAssign(shared_from_this());
}

void AssignNode::evaluatePattern(IPatternExtractor &extractor) {
    extractor.extractAssign(shared_from_this());
}
