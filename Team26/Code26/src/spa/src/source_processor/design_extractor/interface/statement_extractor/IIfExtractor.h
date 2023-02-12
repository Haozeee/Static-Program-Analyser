#pragma once

#include <memory>
#include "source_processor/node/statement_node/IfNode.h"

class IIfExtractor {
 public:
    virtual void extractIf(std::shared_ptr<IfNode> node) = 0;
};
