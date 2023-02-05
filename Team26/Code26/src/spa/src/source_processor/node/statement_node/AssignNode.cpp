#include "AssignNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractSyntaxTreeExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, ExprNode exprNode)
    : StmtNode(stmtIndex), varName(varName), exprNode(exprNode) {}

void AssignNode::evaluate(AbstractSyntaxTreeExtractor &extractor) {
    extractor.extractAssign(std::make_shared<AssignNode>(stmtIndex, varName, exprNode));
}
