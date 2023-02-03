#pragma once

#include <memory>
#include <string>
#include "Node.h"
#include "StmtListNode.h"

class ProcedureNode : public Node {
 public:
    std::string procedureName;
    std::shared_ptr<StmtListNode> stmtListNode;
    ProcedureNode(std::string procedureName, std::shared_ptr<StmtListNode> stmtListNode);
};
