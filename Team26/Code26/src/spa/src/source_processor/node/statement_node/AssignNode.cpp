#include "AssignNode.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, ExprNode exprNode)
    : StmtNode(stmtIndex), varName(varName), exprNode(exprNode) {}

void AssignNode::evaluate(AbstractSyntaxTreeExtractor &extractor) {
}
