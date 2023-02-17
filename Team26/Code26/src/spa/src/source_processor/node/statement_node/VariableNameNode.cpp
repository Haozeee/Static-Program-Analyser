#include "VariableNameNode.h"
#include <utility>

VariableNameNode::VariableNameNode(int stmtIndex, std::string varName, StmtType stmtType) :
    StmtNode(stmtIndex, stmtType), varName(std::move(varName))  {}