#pragma once
#include <memory>
#include "NextTCacheableGraph.h"
#include "NextTReverseCacheableGraph.h"
#include "program_knowledge_base/StorageManager.h"

class Cache {
 private:
     NextTCacheableGraph nextTCache;

     NextTReverseCacheableGraph nextTReverseCache;

 public:
     explicit Cache(StoragePointer storage);

    NextTCacheableGraph* getNextTCache();

    NextTReverseCacheableGraph* getNextTReverseCache();
};
