#include "Store.h"
#include "source_processor/storage_writer/store/PatternStore.h"
#include "source_processor/storage_writer/store/RelationshipStore.h"
#include "source_processor/storage_writer/store/EntityStore.h"

Store::Store(const std::shared_ptr<WriteStorage>& storage) {
    entityStore = std::make_shared<EntityStore>(storage);
    relationshipStore = std::make_shared<RelationshipStore>(storage);
    patternStore = std::make_shared<PatternStore>(storage);
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
