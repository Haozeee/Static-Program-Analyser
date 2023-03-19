#pragma once
#include <memory>
#include "source_processor/node/ProgramNode.h"

class IExtractor {
public:
    virtual void extractProgram(const std::shared_ptr<ProgramNode>& node) = 0;
};