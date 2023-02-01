#include "AssignNode.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, Factor value)
	: StmtNode(stmtIndex), varName(varName), value(value) {};
