#include "PrintNode.h"

#include <utility>
#include "memory"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

PrintNode::PrintNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex, StmtType::STMT_PRINT), varName(std::move(varName)) {}

void PrintNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractPrint(this->shared_from_this());
}
