#pragma once

#include <vector>
#include <memory>
#include "source_processor/storage/interface/IEntityStore.h"
#include "source_processor/storage/interface/IPatternStore.h"
#include "source_processor/storage/interface/IStore.h"
#include "program_knowledge_base/StorageManager.h"

class Store : public IStore {
 private:
    std::shared_ptr<IEntityStore> entityStore;
    std::shared_ptr<IRelationshipStore> relationshipStore;
    std::shared_ptr<IPatternStore> patternStore;

 public:
    explicit Store(const std::shared_ptr<WriteStorage>& storage);

    std::shared_ptr<IEntityStore> getEntityStore() override;
    std::shared_ptr<IPatternStore> getPatternStore() override;
    std::shared_ptr<IRelationshipStore> getRelationshipStore() override;
};
