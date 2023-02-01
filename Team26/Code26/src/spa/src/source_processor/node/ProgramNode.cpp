#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::unique_ptr<ProcedureNode>> procedureList) 
	: procedureList(procedureList) {};
