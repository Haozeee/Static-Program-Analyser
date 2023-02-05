#pragma once

#include "Storage.h"
#include "StorageSingleton.h"
#include "entity/ReadOnlyEntityManager.h"
#include "relationship/ReadOnlyRelationshipManager.h"

class ReadOnlyStorage: public Storage<ReadOnlyRelationshipManager,
        ReadOnlyEntityManager> {
 public:
    explicit ReadOnlyStorage(StorageSingleton* storageSingleton) : Storage(storageSingleton) {}
};
