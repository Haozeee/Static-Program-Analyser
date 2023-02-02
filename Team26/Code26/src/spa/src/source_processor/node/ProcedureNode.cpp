#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(std::string procedureName, std::shared_ptr<StmtListNode> stmtListNode)
    : procedureName(procedureName), stmtListNode(stmtListNode) {}
