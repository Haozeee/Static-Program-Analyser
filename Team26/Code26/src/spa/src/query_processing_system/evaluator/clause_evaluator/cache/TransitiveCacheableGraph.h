#pragma once
#include <unordered_map>
#include <unordered_set>
#include "CacheableGraph.h"

/**
 * Represents the transitive closure of a graph.
 */
class TransitiveCacheableGraph : public CacheableGraph<int, int> {
 protected:
    explicit TransitiveCacheableGraph(StoragePointer storage);

    /**
     * Do DFS on cache miss. Get all items that can be reached from a given starting node.
     * @param node The node to do DFS from.
     */
    void onCacheMiss(int startNode) override;

 public:
    bool isEmpty() override;

    void buildAll() override;
};
