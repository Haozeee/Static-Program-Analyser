#pragma once

#include <string>
#include "source_processor/node/statement_node/AssignNode.h"

class IPatternStore {
 public:
    virtual void insertExpressionPattern(std::shared_ptr<AssignNode> node) = 0;
};
