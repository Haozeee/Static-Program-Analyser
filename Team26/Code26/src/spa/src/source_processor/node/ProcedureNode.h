#pragma once

#include "Node.h"
#include "StmtListNode.h"
#include <memory>
#include <string>

class ProcedureNode : public Node {
 protected:
    std::string procedureName;
    std::unique_ptr<StmtListNode> stmtListNode;

 public:
    ProcedureNode(std::string procedureName, std::unique_ptr<StmtListNode> stmtListNode);
};
