#include "Cache.h"

Cache::Cache(StoragePointer storage) {
    nextTCache = std::make_shared<NextTCacheableGraph>(storage);
    nextTReverseCache = std::make_shared<NextTReverseCacheableGraph>(storage);
}

std::shared_ptr<NextTCacheableGraph> Cache::getNextTCache() {
    return nextTCache;
}

std::shared_ptr<NextTReverseCacheableGraph> Cache::getNextTReverseCache() {
    return nextTReverseCache;
}
