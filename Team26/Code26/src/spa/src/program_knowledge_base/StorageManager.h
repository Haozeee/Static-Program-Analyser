#pragma once

#include <vector>
#include <memory>
#include "Storage.h"
#include "program_knowledge_base/relationship/WriteOnlyRelationshipManager.h"
#include "program_knowledge_base/entity/WriteOnlyEntityManager.h"
#include "program_knowledge_base/pattern/WriteOnlyPatternManager.h"
#include "program_knowledge_base/relationship/ReadOnlyRelationshipManager.h"
#include "program_knowledge_base/entity/ReadOnlyEntityManager.h"
#include "program_knowledge_base/pattern/ReadOnlyPatternManager.h"

using WriteStorage = Storage<WriteOnlyRelationshipManger, WriteOnlyEntityManager, WriteOnlyPatternManager>;
using ReadStroage =  Storage<ReadOnlyRelationshipManager,
        ReadOnlyEntityManager, ReadOnlyPatternManager>;

class StorageManager {
 private:
    std::shared_ptr<StorageUtil> storageUtil;
    StorageManager();
    std::shared_ptr<WriteStorage> getWriteManager();
    std::shared_ptr<ReadStroage> getReadManager();
};
