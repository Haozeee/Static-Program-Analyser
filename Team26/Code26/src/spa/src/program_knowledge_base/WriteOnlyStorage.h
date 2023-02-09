#pragma once

#include <memory>
#include "Storage.h"
#include "StorageUtil.h"
#include "entity/WriteOnlyEntityManager.h"
#include "pattern/WriteOnlyPatternManager.h"
#include "relationship/WriteOnlyRelationshipManager.h"

class WriteOnlyStorage : public Storage<WriteOnlyRelationshipManger,
        WriteOnlyEntityManager, WriteOnlyPatternManager> {
 public:
    explicit WriteOnlyStorage(std::shared_ptr<StorageUtil> storageUtil) : Storage(storageUtil) {}
};
