#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/storage/Store.h"
#include "source_processor/design_extractor/extractor/PatternExtractor.h"

class DesignExtractor {
 private:
    std::shared_ptr<IStore> store;
    std::unique_ptr<EntityExtractor> entityExtractor;
    std::unique_ptr<RelationshipExtractor> relationshipExtractor;
    std::unique_ptr<PatternExtractor> patternExtractor;

 public:
    explicit DesignExtractor(const std::shared_ptr<IStore>& store);
    void extract(const std::shared_ptr<ProgramNode>& programNode);
};
