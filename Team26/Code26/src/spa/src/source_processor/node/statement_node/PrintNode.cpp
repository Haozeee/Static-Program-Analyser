#include "PrintNode.h"

PrintNode::PrintNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}

void PrintNode::evaluate(const AbstractSyntaxTreeExtractor &extractor) {
}
