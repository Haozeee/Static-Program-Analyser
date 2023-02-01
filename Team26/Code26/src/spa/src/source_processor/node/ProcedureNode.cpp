#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::string procedureName, std::unique_ptr<StmtListNode> stmtListNode)
    : procedureName(procedureName), stmtListNode(stmtListNode) {};
