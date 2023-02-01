#pragma once

#include "StmtNode.h"
#include <string>

class ReadNode : public StmtNode {
 protected:
    std::string varName;

 public:
    ReadNode(int stmtIndex, std::string varName);
};
