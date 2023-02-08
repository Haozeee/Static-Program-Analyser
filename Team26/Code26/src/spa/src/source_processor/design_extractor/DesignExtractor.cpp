#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(std::shared_ptr<WriteOnlyStorage> storage) {
    entityStore = std::make_shared<EntityStore>(storage);
    relationshipStore = std::make_shared<RelationshipStore>(storage);
    patternStore = std::make_shared<PatternStore>(storage);

    entityExtractor = std::make_shared<EntityExtractor>(entityStore);
    relationshipExtractor = std::make_shared<RelationshipExtractor>(relationshipStore);
}

void DesignExtractor::extract(std::shared_ptr<ProgramNode> programNode) {
    entityExtractor->extractProgram(programNode);
    relationshipExtractor->extractProgram(programNode);
}
