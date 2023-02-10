#include "AssignNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, std::shared_ptr<ExprNode> exprNode)
    : StmtNode(stmtIndex, StmtType::STMT_ASSIGN), varName(varName), exprNode(exprNode) {}

void AssignNode::evaluate(AbstractExtractor &extractor) {
    extractor.extractAssign(std::make_shared<AssignNode>(stmtIndex, varName, exprNode));
}
