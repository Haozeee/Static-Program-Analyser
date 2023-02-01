#pragma once

#include "StmtNode.h"
#include <string>

class PrintNode : public StmtNode {.
 protected:
    std::string varName;

 public:
    PrintNode(int stmtIndex, std::string varName);
};
