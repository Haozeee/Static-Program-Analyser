#include <memory>
#include <utility>
#include "ReadNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex, StmtType::STMT_READ), varName(std::move(varName)) {}

void ReadNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractRead(this->shared_from_this());
}
