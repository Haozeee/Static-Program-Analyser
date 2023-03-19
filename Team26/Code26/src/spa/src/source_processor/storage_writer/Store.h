#pragma once

#include <vector>
#include <memory>
#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"
#include "source_processor/storage_writer/interface/IStore.h"
#include "program_knowledge_base/StorageManager.h"


class Store : public IStore {
 private:
    std::shared_ptr<IEntityStore> entityStore;
    std::shared_ptr<IRelationshipStore> relationshipStore;
    std::shared_ptr<IPatternStore> patternStore;

 public:
    explicit Store(const std::shared_ptr<WriteStorage>& writeStorage, const std::shared_ptr<ReadStorage>& readStorage);

    std::shared_ptr<IEntityStore> getEntityStore() override;
    std::shared_ptr<IPatternStore> getPatternStore() override;
    std::shared_ptr<IRelationshipStore> getRelationshipStore() override;
};
