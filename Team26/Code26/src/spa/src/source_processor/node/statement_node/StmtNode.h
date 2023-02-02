#pragma once

#include "source_processor/node/Node.h"

class StmtNode : public Node {
 protected:
    int stmtIndex;

 public:
    explicit StmtNode(int stmtIndex);
};
