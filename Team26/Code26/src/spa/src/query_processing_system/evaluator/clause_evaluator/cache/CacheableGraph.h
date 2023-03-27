#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "../RelationResultType.h"
#include "program_knowledge_base/StorageManager.h"

using ProgrammeStore = std::shared_ptr<ReadStorage>;

template<typename T, typename U>
class CacheableGraph {
 protected:
    /**
     * Stores the cached data.
     */
    std::unordered_map<T, std::unordered_set<U>> cache;

    /**
     * Location to get data from in the event of a cache miss.
     */
    std::unordered_map<T, std::unordered_set<U>> base;

    ProgrammeStore storage;

    explicit CacheableGraph(ProgrammeStore storage) : storage(storage) {}

    /**
     * In the event of a cache miss, get the data from base and insert into cache.
     */
    virtual void onCacheMiss(T query) = 0;

    /**
     * Set the base of the cache.
     */
    virtual void setBase() {}

 public:
    /**
     * Insert an item into the cache. If the item is already in cache, do nothing.
     * @param item Item to insert.
     */
    void insertIntoCache(T item) {
        if (!cache.count(item)) {
            onCacheMiss(item);
        }
    }

    /**
     * Insert multiple items into cache.
     */
    void insertItemsIntoCache(std::unordered_set<T> itemsToAdd) {
        for (int item : itemsToAdd) {
            insertIntoCache(item);
        }
    }

    /**
     * Get the entire cache.
     */
    std::unordered_map<T, std::unordered_set<U>> getCacheData() {
        return cache;
    }

    /**
     * Build the entire cache.
     */
    virtual void buildAll() = 0;

    virtual bool isEmpty() = 0;
};
