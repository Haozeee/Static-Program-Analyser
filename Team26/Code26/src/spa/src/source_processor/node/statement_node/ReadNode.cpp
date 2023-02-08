#include "ReadNode.h"
#include "memory"
#include "source_processor/design_extractor/extractor/AbstractExtractor.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}

void ReadNode::evaluate(AbstractExtractor &extractor) {
    extractor.extractRead(std::make_shared<ReadNode>(stmtIndex, varName));
}
