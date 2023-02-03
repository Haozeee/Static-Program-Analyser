#include "CallNode.h"

CallNode::CallNode(int stmtIndex, std::string processName): StmtNode(stmtIndex), processName(processName) {}

void CallNode::evaluate(const AbstractSyntaxTreeExtractor &extractor) {
}
