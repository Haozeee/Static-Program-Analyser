#include "StmtListNode.h"

StmtListNode::StmtListNode(std::vector<std::unique_ptr<StmtNode>> stmtList) : stmtList(stmtList) {};
