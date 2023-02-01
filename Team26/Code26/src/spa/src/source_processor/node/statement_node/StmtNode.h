#pragma once

#include "../Node.h"

class StmtNode : public Node {
 protected: 
    int stmtIndex;

 public:
    StmtNode(int stmtIndex);
};
