#pragma once

#include <memory>
#include <string>
#include "Node.h"
#include "StmtListNode.h"

class ProcedureNode : public Node {
 protected:
    std::string procedureName;
    std::shared_ptr<StmtListNode> stmtListNode;

 public:
    ProcedureNode(std::string procedureName, std::shared_ptr<StmtListNode> stmtListNode);
};
