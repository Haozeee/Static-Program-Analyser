#pragma once

#include "source_processor/node/Node.h"

class StmtNode : public Node {
 public:
    int stmtIndex;
    explicit StmtNode(int stmtIndex);
};
