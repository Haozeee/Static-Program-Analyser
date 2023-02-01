#pragma once

#include "StmtNode.h"
#include <string>

class CallNode : public StmtNode {
protected:
    std::string processName;

public:
    CallNode(int stmtIndex, std::string processName);
};
