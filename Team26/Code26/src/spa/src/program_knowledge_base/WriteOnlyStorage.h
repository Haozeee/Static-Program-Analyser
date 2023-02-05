#pragma once

#include "Storage.h"
#include "StorageSingleton.h"
#include "entity/WriteOnlyEntityManager.h"
#include "relationship/WriteOnlyRelationshipManager.h"

class WriteOnlyStorage : public Storage<WriteOnlyRelationshipManger,
        WriteOnlyEntityManager> {
 public:
    explicit WriteOnlyStorage(StorageSingleton* storageSingleton) : Storage(storageSingleton) {}
};
