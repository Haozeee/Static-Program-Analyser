#pragma once

#include <memory>
#include <string>
#include "Node.h"
#include "StmtListNode.h"

class ProcedureNode : public Node {
 public:
    const std::string procedureName;
    const std::shared_ptr<StmtListNode> stmtListNode;

    ProcedureNode(std::string procedureName, std::shared_ptr<StmtListNode> stmtListNode);
};
