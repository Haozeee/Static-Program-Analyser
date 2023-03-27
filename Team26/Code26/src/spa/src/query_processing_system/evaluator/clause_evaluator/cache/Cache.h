#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "NextTCacheableGraph.h"
#include "NextTReverseCacheableGraph.h"
#include "AffectsCacheableGraph.h"
#include "AffectsTCacheableGraph.h"
#include "AffectsTReverseCacheableGraph.h"
#include "program_knowledge_base/StorageManager.h"

class Cache {
 private:
     NextTCacheableGraph nextTCache;

     NextTReverseCacheableGraph nextTReverseCache;

     AffectsCacheableGraph affectsCache;

     AffectsTCacheableGraph affectsTCache;

     AffectsTReverseCacheableGraph affectsTReverseCache;

     /**
      * AffectsT is expensive to initialise as it requires the entire affects
      * to be completed. Hence, only initialise it when it is called.
      * The boolean keeps track if it is initialized.
      */
     bool affectsTInitialised = false;

     bool affectsTReverseInitialised = false;

     void setCacheBase();

 public:
     explicit Cache(ProgrammeStore storage);

    NextTCacheableGraph* getNextTCache();

    NextTReverseCacheableGraph* getNextTReverseCache();

    AffectsCacheableGraph* getAffectsCache();

    AffectsTCacheableGraph* getAffectsTCache();

    AffectsTReverseCacheableGraph* getAffectsTReverseCache();

    /**
     * We do not store an affects reverse cache directly. If we want the reverse relationship
     * data for cache, we need to get it from the affects cache.
     * @return The affects reverse cache data.
     */
    StmtStmtMap getAffectsReverseCacheData();

    /**
     * Insert some data into the cache before getting the data stored in the cache.
     * @param cacheGraph The cache to get the data from.
     * @param itemToInsert The data that is to be inserted into the cache before reading from it.
     * @return The new data from the cache.
     */
    static StmtStmtMap getCacheData(CacheableGraph<int, int>* cacheGraph, std::unordered_set<int> &itemToInsert);

    /**
     * Inset data into a cache.
     * @param cacheGraph The cache to insert the data into.
     * @param itemToInsert The items that are to be inserted into the cache.
     */
    static void insertDataToCache(CacheableGraph<int, int>* cacheGraph, std::unordered_set<int> &itemToInsert);

    /**
     * Checks if a given cache is empty.
     * @param cacheGraph The cache to be checked.
     * @return True if the cache is empty, false otherwise.
     */
    static bool isCacheEmpty(CacheableGraph<int, int>* cacheGraph);

    /**
     * Build the entire cache. Ensures that all items are inserted into the cache.
     * @param cacheGraph The cache to be build.
     */
    static void buildEntireCache(CacheableGraph<int, int>* cacheGraph);

    /**
     * Build the entire cache and get the cache data. This method is to be used when
     * we are interested in all items that can be in the cache, so that there will be no cache misses.
     * @param cacheGraph
     */
    static StmtStmtMap getEntireCacheData(CacheableGraph<int, int>* cacheGraph);
};
