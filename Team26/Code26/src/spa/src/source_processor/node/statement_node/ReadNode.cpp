#include "ReadNode.h"

ReadNode::ReadNode(int stmtIndex, std::string varName)
    : StmtNode(stmtIndex), varName(varName) {}
