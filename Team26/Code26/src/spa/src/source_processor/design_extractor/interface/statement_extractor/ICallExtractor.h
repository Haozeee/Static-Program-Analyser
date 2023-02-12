#pragma once

#include <memory>
#include "source_processor/node/statement_node/CallNode.h"

class ICallExtractor {
 public:
    virtual void extractCall(std::shared_ptr<CallNode> node) = 0;
};
