#pragma once
#include "CacheableGraph.h"
#include <unordered_map>
#include <unordered_set>

/**
 * Represents the transitive closure of a graph.
 */
class TransitiveCacheableGraph : public CacheableGraph {
protected:
    explicit TransitiveCacheableGraph(StoragePointer storage);

    /**
     * Do DFS on cache miss.
     */
    std::unordered_set<int> onCacheMiss(int query) override;
};
