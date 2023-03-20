#include <utility>
#include "ReadNode.h"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : VariableNameNode(stmtIndex, std::move(varName), StmtType::STMT_READ) {}

void ReadNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractRead(this->shared_from_this());
}
