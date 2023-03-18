#include "ProcedureNode.h"

#include <utility>

ProcedureNode::ProcedureNode(std::string procedureName, std::shared_ptr<StmtListNode> stmtListNode)
    : procedureName(std::move(procedureName)), stmtListNode(std::move(stmtListNode)) {}
