#pragma once

#include "Node.h"
#include "ProcedureNode.h"
#include <memory>
#include <string>

class ProgramNode : public Node {
 protected:
    std::vector<std::unique_ptr<ProcedureNode>> procedureList;

 public:
    ProgramNode(std::vector<std::unique_ptr<ProcedureNode>> procedureList);
};
