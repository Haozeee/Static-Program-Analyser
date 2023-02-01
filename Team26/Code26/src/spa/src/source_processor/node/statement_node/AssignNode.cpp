#include "AssignNode.h"

AssignNode::AssignNode(int stmtIndex, std::string varName, int value)
	: StmtNode(stmtIndex), varName(varName), value(value) {};
