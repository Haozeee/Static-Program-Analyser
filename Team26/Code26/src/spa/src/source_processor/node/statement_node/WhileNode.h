#pragma once

#include "StmtNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/StmtListNode.h"

class WhileNode : public StmtNode {
 public:
     CondExprNode condExprNode;
     StmtListNode stmtListNode;

     WhileNode(int stmtIndex, CondExprNode condExprNode, StmtListNode stmtListNode);
};
