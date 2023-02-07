#include "WhileNode.h"

WhileNode::WhileNode(int stmtIndex, CondExprNode condExprNode, StmtListNode stmtListNode)
    : StmtNode(stmtIndex), condExprNode(condExprNode), stmtListNode(stmtListNode) {}