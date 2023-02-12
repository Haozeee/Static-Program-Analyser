#pragma once

#include <memory>
#include "source_processor/node/statement_node/ReadNode.h"

class IReadExtractor {
 public:
    virtual void extractRead(std::shared_ptr<ReadNode> node) = 0;
};
