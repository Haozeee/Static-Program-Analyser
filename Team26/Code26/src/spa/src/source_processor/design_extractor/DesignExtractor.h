#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/storage/EntityStore.h"
#include "source_processor/storage/RelationshipStore.h"
#include "source_processor/storage/PatternStore.h"

class DesignExtractor {
 private:
    std::shared_ptr<EntityExtractor> entityExtractor;
    std::shared_ptr<RelationshipExtractor> relationshipExtractor;

    std::shared_ptr<EntityStore> entityStore;
    std::shared_ptr<RelationshipStore> relationshipStore;
    std::shared_ptr<PatternStore> patternStore;

 public:
    explicit DesignExtractor(const std::shared_ptr<WriteOnlyStorage>& storage);
    void extract(const std::shared_ptr<ProgramNode>& programNode);
};
