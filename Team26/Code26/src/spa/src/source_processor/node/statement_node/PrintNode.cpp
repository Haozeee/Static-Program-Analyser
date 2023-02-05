#include "PrintNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractSyntaxTreeExtractor.h"

PrintNode::PrintNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}

void PrintNode::evaluate(AbstractSyntaxTreeExtractor &extractor) {
    extractor.extractPrint(std::make_shared<PrintNode>(stmtIndex, varName));
}
