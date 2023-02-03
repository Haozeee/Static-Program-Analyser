#pragma once

#include "source_processor/node/Node.h"

class AbstractSyntaxTreeExtractor;  // forward declaration

class StmtNode : public Node {
 public:
    int stmtIndex;

    virtual void evaluate(const AbstractSyntaxTreeExtractor& extractor) = 0;
    explicit StmtNode(int stmtIndex);
};
