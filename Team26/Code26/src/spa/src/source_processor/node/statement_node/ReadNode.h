#pragma once

#include <string>
#include "StmtNode.h"

class ReadNode : public StmtNode {
 public:
    std::string varName;
    ReadNode(int stmtIndex, std::string varName);
};
