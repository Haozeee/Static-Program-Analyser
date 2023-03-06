#include "CallNode.h"
#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

CallNode::CallNode(int stmtIndex, std::string procedureName)
    : StmtNode(stmtIndex, StmtType::STMT_CALL), procedureName(std::move(procedureName)) {}

void CallNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractCall(this->shared_from_this());
}
