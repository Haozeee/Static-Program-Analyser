#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Node.h"
#include "ProcedureNode.h"

class ProgramNode : public Node {
 public:
    std::vector<std::shared_ptr<ProcedureNode>> procedureList;

    explicit ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedureList);
};
