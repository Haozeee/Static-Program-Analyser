#include "Cache.h"

Cache::Cache(StoragePointer storage) :
        nextTCache(NextTCacheableGraph(storage)),
        nextTReverseCache(storage) {
    nextTCache.setBase();
    nextTReverseCache.setBase();
}

NextTCacheableGraph* Cache::getNextTCache() {
    return &nextTCache;
}

NextTReverseCacheableGraph* Cache::getNextTReverseCache() {
    return &nextTReverseCache;
}
