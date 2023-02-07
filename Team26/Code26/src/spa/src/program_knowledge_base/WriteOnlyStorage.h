#pragma once

#include "Storage.h"
#include "StorageUtil.h"
#include "entity/WriteOnlyEntityManager.h"
#include "relationship/WriteOnlyRelationshipManager.h"

class WriteOnlyStorage : public Storage<WriteOnlyRelationshipManger,
        WriteOnlyEntityManager> {
 public:
    explicit WriteOnlyStorage(StorageUtil* storageUtil) : Storage(storageUtil) {}
};
