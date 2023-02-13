#include "PrintNode.h"
#include "memory"
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

PrintNode::PrintNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex, StmtType::STMT_PRINT), varName(varName) {}

void PrintNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractPrint(std::make_shared<PrintNode>(stmtIndex, varName));
}
