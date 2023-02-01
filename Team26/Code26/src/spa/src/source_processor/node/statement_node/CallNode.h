#pragma once

#include <string>
#include "StmtNode.h"

class CallNode : public StmtNode {
 protected:
    std::string processName;

 public:
    CallNode(int stmtIndex, std::string processName);
};
