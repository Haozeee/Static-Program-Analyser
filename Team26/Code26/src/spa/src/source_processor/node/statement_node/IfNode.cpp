#include "IfNode.h"

IfNode::IfNode(int stmtIndex, CondExprNode condExprNode, StmtListNode thenStmtListNode, StmtListNode elseStmtListNode)
    : StmtNode(stmtIndex), condExprNode(condExprNode), thenStmtListNode(thenStmtListNode), elseStmtListNode(elseStmtListNode) {}