#pragma once
#include <unordered_map>
#include <unordered_set>
#include "program_knowledge_base/StorageManager.h"

using StoragePointer = std::shared_ptr<ReadStorage>;

using GraphType = std::unordered_map<int, std::unordered_set<int>>;

class CacheableGraph {
 protected:
    /**
     * Stores the cached data.
     */
    GraphType cache;

    /**
     * Location to get data from in the event of a cache miss.
     */
    GraphType base;

    StoragePointer storage;

    explicit CacheableGraph(StoragePointer storage);

    /**
     * In the event of a cache miss, get the data from base.
     */
    virtual std::unordered_set<int> onCacheMiss(int query) = 0;

    /**
     * Set the base of the cache.
     */
    virtual GraphType getBase() = 0;

 public:
    /**
     * Given a query, get the corresponding data from the cache. If item is not in the cache,
     * gets the data from base and add it into the cache.
     * @param query The data to search the cache for.
     * @return The value mapped to query.
     */
    std::unordered_set<int> getFromCache(int query);
};
