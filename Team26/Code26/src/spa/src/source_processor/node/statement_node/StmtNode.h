#pragma once

#include "source_processor/node/Node.h"
#include "source_processor/extractor/AbstractSyntaxTreeExtractor.h"

class StmtNode : public Node {
 public:
    int stmtIndex;

    virtual void evaluate(const AbstractSyntaxTreeExtractor& extractor) = 0;

    explicit StmtNode(int stmtIndex);
};
