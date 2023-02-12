#include "AssignNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode)
    : StmtNode(stmtIndex, StmtType::STMT_ASSIGN), varName(varName), exprNode(exprNode) {}

void AssignNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractAssign(std::make_shared<AssignNode>(stmtIndex, varName, exprNode));
}
