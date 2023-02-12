#pragma once

#include <memory>
#include "source_processor/node/statement_node/WhileNode.h"

class IWhileExtractor {
 public:
    virtual void extractWhile(std::shared_ptr<WhileNode> node) = 0;
};
