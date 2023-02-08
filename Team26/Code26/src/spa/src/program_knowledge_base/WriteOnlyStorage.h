#pragma once

#include <memory>
#include "Storage.h"
#include "StorageUtil.h"
#include "entity/WriteOnlyEntityManager.h"
#include "relationship/WriteOnlyRelationshipManager.h"

class WriteOnlyStorage : public Storage<WriteOnlyRelationshipManger,
        WriteOnlyEntityManager> {
 public:
    explicit WriteOnlyStorage(std::shared_ptr<StorageUtil> storageUtil) : Storage(storageUtil) {}
};
