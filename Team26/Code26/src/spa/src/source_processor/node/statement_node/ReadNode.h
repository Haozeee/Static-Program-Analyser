#pragma once

#include <string>
#include "StmtNode.h"

class ReadNode : public StmtNode {
 protected:
    std::string varName;

 public:
    ReadNode(int stmtIndex, std::string varName);
};
