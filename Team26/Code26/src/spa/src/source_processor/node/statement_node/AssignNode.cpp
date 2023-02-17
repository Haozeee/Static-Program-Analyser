#include "AssignNode.h"

#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"
#include "source_processor/design_extractor/interface/IPatternExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode)
    : VariableNameNode(stmtIndex, std::move(varName), StmtType::STMT_ASSIGN) , exprNode(std::move(exprNode)) {}

void AssignNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractAssign(this->shared_from_this());
}

void AssignNode::evaluatePattern(IPatternExtractor &extractor) {
    extractor.extractAssign(this->shared_from_this());
}
