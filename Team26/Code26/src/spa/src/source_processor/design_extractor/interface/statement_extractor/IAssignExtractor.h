#pragma once

#include <memory>
#include "source_processor/node/statement_node/AssignNode.h"

class AssignNode;

class IAssignExtractor {
 public:
    virtual void extractAssign(std::shared_ptr<AssignNode> node) = 0;
};
