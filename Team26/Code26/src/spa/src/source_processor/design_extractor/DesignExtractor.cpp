#include "DesignExtractor.h"
#include "source_processor/design_extractor/extractor/EntityExtractor.h"
#include "source_processor/design_extractor/extractor/RelationshipExtractor.h"
#include "source_processor/design_extractor/extractor/PatternExtractor.h"

DesignExtractor::DesignExtractor(const std::shared_ptr<IStore>& store) {
    entityExtractor = std::make_unique<EntityExtractor>(store->getEntityStore());
    relationshipExtractor = std::make_unique<RelationshipExtractor>(store->getRelationshipStore());
    patternExtractor = std::make_unique<PatternExtractor>(store->getPatternStore());
}

void DesignExtractor::extract(const std::shared_ptr<ProgramNode>& programNode) {
    entityExtractor->extractProgram(programNode);
    relationshipExtractor->extractProgram(programNode);
    patternExtractor->extractProgram(programNode);
}
