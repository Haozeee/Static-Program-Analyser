#include "StmtListNode.h"

StmtListNode::StmtListNode(std::vector<std::shared_ptr<StmtNode>> stmtList)
    : stmtList(stmtList) {}
