#pragma once

#include <memory>
#include "Storage.h"
#include "StorageUtil.h"
#include "entity/ReadOnlyEntityManager.h"
#include "pattern/ReadOnlyPatternManager.h"
#include "relationship/ReadOnlyRelationshipManager.h"

class ReadOnlyStorage: public Storage<ReadOnlyRelationshipManager,
        ReadOnlyEntityManager, ReadOnlyPatternManager> {
 public:
    explicit ReadOnlyStorage(std::shared_ptr<StorageUtil> storageUtil) : Storage(storageUtil) {}
};
