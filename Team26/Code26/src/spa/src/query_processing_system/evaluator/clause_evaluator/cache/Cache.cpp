#include "Cache.h"

Cache::Cache(StoragePointer storage) :
        nextTCache(storage),
        nextTReverseCache(storage),
        affectsCache(storage),
        affectsReverseCache(storage),
        affectsTCache(storage),
        affectsTReverseCache(storage) { setCacheBase(); }

void Cache::setCacheBase() {
    nextTCache.setBase();
    nextTReverseCache.setBase();
    affectsCache.setBase();
    affectsReverseCache.setBase();
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

AffectsReverseCacheableGraph* Cache::getAffectsReverseCacheableGraph() {
    return &affectsReverseCache;
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
        affectsReverseCache.buildAll();
        affectsTReverseCache.setBase(affectsReverseCache.getCacheData());
        affectsTReverseInitialised = true;
    }
    return &affectsTReverseCache;
}
