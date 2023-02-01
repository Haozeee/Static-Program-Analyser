#pragma once

#include <string>
#include "StmtNode.h"

class AssignNode : public StmtNode {
 protected:
    std::string varName;
    int value;

 public:
    // TODO(oviya): Replace with Expr
    AssignNode(int stmtIndex, std::string varName, int value);
};
