#include "Store.h"

Store::Store(const std::shared_ptr<WriteOnlyStorage>& storage) {
    entityStore = std::make_shared<EntityStore>(storage);
    relationshipStore = std::make_shared<RelationshipStore>(storage);
    patternStore = std::make_shared<PatternStore>(storage);
}

std::shared_ptr<EntityStore> Store::getEntityStore() {
    return entityStore;
}

std::shared_ptr<PatternStore> Store::getPatternStore() {
    return patternStore;
}

std::shared_ptr<RelationshipStore> Store::getRelationshipStore() {
    return relationshipStore;
}
