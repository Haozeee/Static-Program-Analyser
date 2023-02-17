#pragma once

#include "StmtNode.h"
#include <string>

class VariableNameNode : public StmtNode {
 public:
    const std::string varName;

    VariableNameNode(int stmtIndex, std::string varName, StmtType type);
};
