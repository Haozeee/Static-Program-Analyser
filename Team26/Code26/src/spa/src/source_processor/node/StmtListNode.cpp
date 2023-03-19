#include "StmtListNode.h"

#include <utility>

StmtListNode::StmtListNode(std::vector<std::shared_ptr<StmtNode>> stmtList)
    : stmtList(std::move(stmtList)) {}
