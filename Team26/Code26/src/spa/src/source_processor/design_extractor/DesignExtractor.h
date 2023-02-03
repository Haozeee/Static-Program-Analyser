#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"

class DesignExtractor {
 private:
    std::shared_ptr<EntityExtractor> entityExtractor;

 public:
    explicit DesignExtractor(std::shared_ptr<WriteOnlyStorage> storage);
    void extract(std::shared_ptr<ProgramNode> programNode);
};
