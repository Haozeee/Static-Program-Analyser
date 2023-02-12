#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/storage/Store.h"

class DesignExtractor {
 private:
    std::shared_ptr<Store> store;
    std::unique_ptr<EntityExtractor> entityExtractor;
    std::unique_ptr<RelationshipExtractor> relationshipExtractor;

 public:
    explicit DesignExtractor(std::shared_ptr<Store> store);
    void extract(const std::shared_ptr<ProgramNode>& programNode);
};
