#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(const std::shared_ptr<IStore>& store, const std::shared_ptr<ReadStorage>&
        readStorage) {
    entityExtractor = std::make_unique<EntityExtractor>(store->getEntityStore(), store->getPatternStore());
    relationshipExtractor = std::make_unique<RelationshipExtractor>(store->getRelationshipStore());
}

void DesignExtractor::extract(const std::shared_ptr<ProgramNode>& programNode) {
    entityExtractor->extractProgram(programNode);
    relationshipExtractor->extractProgram(programNode);
}
