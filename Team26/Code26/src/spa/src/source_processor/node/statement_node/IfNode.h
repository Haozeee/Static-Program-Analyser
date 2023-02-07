#pragma once

#include "StmtNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/StmtListNode.h"

class IfNode : public StmtNode {
 public:
     CondExprNode condExprNode;
     StmtListNode thenStmtListNode;
     StmtListNode elseStmtListNode;

    IfNode(int stmtIndex, CondExprNode condExprNode, StmtListNode thenStmtListNode, StmtListNode elseStmtListNode);
};
