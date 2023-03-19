#include "Store.h"
#include "source_processor/storage_writer/store/PatternStore.h"
#include "source_processor/storage_writer/store/RelationshipStore.h"
#include "source_processor/storage_writer/store/EntityStore.h"

Store::Store(const std::shared_ptr<WriteStorage>& writeStorage, const std::shared_ptr<ReadStorage>& readStorage) {
    entityStore = std::make_shared<EntityStore>(writeStorage);
    relationshipStore = std::make_shared<RelationshipStore>(writeStorage, readStorage);
    patternStore = std::make_shared<PatternStore>(writeStorage);
}

std::shared_ptr<IEntityStore> Store::getEntityStore() {
    return entityStore;
}

std::shared_ptr<IPatternStore> Store::getPatternStore() {
    return patternStore;
}

std::shared_ptr<IRelationshipStore> Store::getRelationshipStore() {
    return relationshipStore;
}
