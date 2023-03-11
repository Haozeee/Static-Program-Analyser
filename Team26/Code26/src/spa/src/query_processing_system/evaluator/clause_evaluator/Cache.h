#pragma once
#include <memory>
#include "cache/NextTCacheableGraph.h"
#include "cache/NextTReverseCacheableGraph.h"
#include "../../../program_knowledge_base/StorageManager.h"

class Cache {
 private:
     std::shared_ptr<NextTCacheableGraph> nextTCache;

     std::shared_ptr<NextTReverseCacheableGraph> nextTReverseCache;

 public:
     explicit Cache(StoragePointer storage);

    std::shared_ptr<NextTCacheableGraph> getNextTCache();

    std::shared_ptr<NextTReverseCacheableGraph> getNextTReverseCache();
};
