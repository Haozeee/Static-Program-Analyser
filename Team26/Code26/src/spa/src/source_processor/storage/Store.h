#pragma once

#include <vector>
#include <memory>
#include "source_processor/storage/store/EntityStore.h"
#include "source_processor/storage/store/RelationshipStore.h"
#include "source_processor/storage/store/PatternStore.h"

class Store {
 private:
    std::shared_ptr<EntityStore> entityStore;
    std::shared_ptr<RelationshipStore> relationshipStore;
    std::shared_ptr<PatternStore> patternStore;
 public:
    explicit Store(const std::shared_ptr<WriteOnlyStorage>& storage);

    std::shared_ptr<EntityStore> getEntityStore();
    std::shared_ptr<PatternStore> getPatternStore();
    std::shared_ptr<RelationshipStore> getRelationshipStore();
};
