#include "CallNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractExtractor.h"

CallNode::CallNode(int stmtIndex, std::string processName)
    : StmtNode(stmtIndex, StmtType::STMT_CALL), processName(processName) {}

void CallNode::evaluate(AbstractExtractor &extractor) {
    extractor.extractCall(std::make_shared<CallNode>(stmtIndex, processName));
}
