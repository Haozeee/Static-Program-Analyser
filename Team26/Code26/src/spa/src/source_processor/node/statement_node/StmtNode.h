#pragma once

#include "source_processor/node/Node.h"

class AbstractExtractor;

class StmtNode : public Node {
 public:
    int stmtIndex;

    virtual void evaluate(AbstractExtractor& extractor) = 0;
    explicit StmtNode(int stmtIndex);
};
