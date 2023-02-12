#include "DesignExtractor.h"

void DesignExtractor::extract(const std::shared_ptr<ProgramNode>& programNode) {
    entityExtractor->extractProgram(programNode);
    relationshipExtractor->extractProgram(programNode);
}

DesignExtractor::DesignExtractor(std::shared_ptr<Store> store) {
    entityExtractor = std::make_unique<EntityExtractor>(store->getEntityStore());
    relationshipExtractor = std::make_unique<RelationshipExtractor>(store->getRelationshipStore());
}
