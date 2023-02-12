#pragma once

#include <memory>
#include "source_processor/node/statement_node/PrintNode.h"

class IPrintExtractor {
 public:
    virtual void extractPrint(std::shared_ptr<PrintNode> node) = 0;
};
