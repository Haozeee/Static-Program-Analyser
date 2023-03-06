#pragma once

#include <memory>
#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"

class IStore {
 public:
    virtual std::shared_ptr<IEntityStore> getEntityStore() = 0;
    virtual std::shared_ptr<IPatternStore> getPatternStore() = 0;
    virtual std::shared_ptr<IRelationshipStore> getRelationshipStore() = 0;
};
