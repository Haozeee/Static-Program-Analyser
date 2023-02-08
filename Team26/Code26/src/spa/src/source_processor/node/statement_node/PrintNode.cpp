#include "PrintNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractExtractor.h"

PrintNode::PrintNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}

void PrintNode::evaluate(AbstractExtractor &extractor) {
    extractor.extractPrint(std::make_shared<PrintNode>(stmtIndex, varName));
}
