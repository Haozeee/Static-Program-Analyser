#pragma once

#include "source_processor/node/ProgramNode.h"

class DesignExtractor {
    DesignExtractor();
    void extract(std::shared_ptr<ProgramNode> programNode);
};
