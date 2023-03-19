#include "ProgramNode.h"

#include <utility>

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedureList)
    : procedureList(std::move(procedureList)) {}
