#include "DesignExtractor.h"

void DesignExtractor::extract(std::shared_ptr<ProgramNode> programNode) {
}

DesignExtractor::DesignExtractor(std::shared_ptr<WriteOnlyStorage> storage) {
    entityExtractor = std::make_shared<EntityExtractor>(storage);
}
