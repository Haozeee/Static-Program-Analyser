#include "Cache.h"

Cache::Cache(std::shared_ptr<ReadStorage> storage) :
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

AffectsCacheableGraph* Cache::getAffectsCache() {
    return &affectsCache;
}

std::unordered_map<int, std::unordered_set<int>> Cache::getAffectsReverseCacheData() {
    return affectsCache.getReverseCache();
}

AffectsTCacheableGraph* Cache::getAffectsTCache() {
    if (!affectsTInitialised) {
        affectsCache.buildAll();
        affectsTCache.setBase(affectsCache.getCacheData());
        affectsTInitialised = true;
    }
    return &affectsTCache;
}

AffectsTReverseCacheableGraph* Cache::getAffectsTReverseCache() {
    if (!affectsTReverseInitialised) {
        affectsCache.buildAll();
        affectsTReverseCache.setBase(affectsCache.getReverseCache());
        affectsTReverseInitialised = true;
    }
    return &affectsTReverseCache;
}

StmtStmtMap Cache::getCacheData(CacheableGraph<int, int> *cacheGraph, std::unordered_set<int> &itemToInsert) {
    insertDataToCache(cacheGraph, itemToInsert);
    return cacheGraph->getCacheData();
}

void Cache::insertDataToCache(CacheableGraph<int, int>* cacheGraph, std::unordered_set<int> &itemToInsert) {
    cacheGraph->insertItemsIntoCache(itemToInsert);
}

bool Cache::isCacheEmpty(CacheableGraph<int, int>* cacheGraph) {
    return cacheGraph->isEmpty();
}

void Cache::buildEntireCache(CacheableGraph<int, int>* cacheGraph) {
    cacheGraph->buildAll();
}

StmtStmtMap Cache::getEntireCacheData(CacheableGraph<int, int> *cacheGraph) {
    buildEntireCache(cacheGraph);
    return cacheGraph->getCacheData();
}
