#include "Cache.h"

Cache::Cache(StoragePointer storage) :
        nextTCache(storage),
        nextTReverseCache(storage),
        affectsCache(storage),
        affectsTCache(storage),
        affectsTReverseCache(storage) { setCacheBase(); }

void Cache::setCacheBase() {
    nextTCache.setBase();
    nextTReverseCache.setBase();
    affectsCache.setBase();
}

NextTCacheableGraph* Cache::getNextTCache() {
    return &nextTCache;
}

NextTReverseCacheableGraph* Cache::getNextTReverseCache() {
    return &nextTReverseCache;
}

AffectsCacheableGraph* Cache::getAffectsCacheableGraph() {
    return &affectsCache;
}

AffectsTCacheableGraph* Cache::getAffectsTCacheableGraph() {
    if (!affectsTInitialised) {
        affectsCache.buildAll();
        affectsTCache.setBase(affectsCache.getCacheData());
        affectsTInitialised = true;
    }
    return &affectsTCache;
}

AffectsTReverseCacheableGraph* Cache::getAffectsTReverseCacheableGraph() {
    if (!affectsTReverseInitialised) {
        affectsCache.buildAll();
        affectsTReverseCache.setBase(affectsCache.getReverseCache());
        affectsTReverseInitialised = true;
    }
    return &affectsTReverseCache;
}
