#pragma once

#include <memory>
#include <string>
#include "Node.h"
#include "ProcedureNode.h"

class ProgramNode : public Node {
 protected:
    std::vector<std::shared_ptr<ProcedureNode>> procedureList;

 public:
    ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedureList);
};
