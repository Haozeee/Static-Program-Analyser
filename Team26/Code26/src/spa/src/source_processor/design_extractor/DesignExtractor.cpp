#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(std::shared_ptr<WriteOnlyStorage> storage) {
    entityExtractor = std::make_shared<EntityExtractor>(storage);
    relationshipExtractor = std::make_shared<RelationshipExtractor>(storage);
}

void DesignExtractor::extract(std::shared_ptr<ProgramNode> programNode) {
    entityExtractor->extractProgram(programNode);
    relationshipExtractor->extractProgram(programNode);
}
