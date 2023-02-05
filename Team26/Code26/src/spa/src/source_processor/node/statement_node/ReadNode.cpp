#include "ReadNode.h"
#include "source_processor/design_extractor/extractor/AbstractSyntaxTreeExtractor.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}

void ReadNode::evaluate(AbstractSyntaxTreeExtractor &extractor) {
    extractor.extractRead(std::make_shared<ReadNode>(stmtIndex, varName));
}
