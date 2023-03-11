#include "CacheableGraph.h"

CacheableGraph::CacheableGraph(StoragePointer storage) : storage(storage), base(getBase()) {}

std::unordered_set<int> CacheableGraph::getFromCache(int query) {
    if (cache.count(query)) {
        return cache.at(query);
    }
    return onCacheMiss(query);
}
