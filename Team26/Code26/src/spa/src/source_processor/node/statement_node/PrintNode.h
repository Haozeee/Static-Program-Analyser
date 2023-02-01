#pragma once

#include <string>
#include "StmtNode.h"

class PrintNode : public StmtNode {
 protected:
    std::string varName;

 public:
    PrintNode(int stmtIndex, std::string varName);
};
