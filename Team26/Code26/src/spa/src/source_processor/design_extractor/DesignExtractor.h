#pragma once

#include <memory>

#include "source_processor/node/ProgramNode.h"

class DesignExtractor {
 public:
    DesignExtractor();
    void extract(std::shared_ptr<ProgramNode> programNode);
};
