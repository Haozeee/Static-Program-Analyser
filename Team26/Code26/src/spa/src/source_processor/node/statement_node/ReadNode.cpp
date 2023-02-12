#include <memory>
#include "ReadNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex, StmtType::STMT_READ), varName(varName) {}

void ReadNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractRead(std::make_shared<ReadNode>(stmtIndex, varName));
}
