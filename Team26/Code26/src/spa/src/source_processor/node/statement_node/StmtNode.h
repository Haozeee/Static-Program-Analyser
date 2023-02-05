#pragma once

#include "source_processor/node/Node.h"

class AbstractSyntaxTreeExtractor;

class StmtNode : public Node {
 public:
    int stmtIndex;

    virtual void evaluate(AbstractSyntaxTreeExtractor& extractor) = 0;
    explicit StmtNode(int stmtIndex);
};
