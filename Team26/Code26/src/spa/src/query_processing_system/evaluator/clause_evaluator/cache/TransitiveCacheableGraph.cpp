#include "TransitiveCacheableGraph.h"

TransitiveCacheableGraph::TransitiveCacheableGraph(StoragePointer storage) : CacheableGraph<int, int>(storage) {}

void TransitiveCacheableGraph::onCacheMiss(int query) {
    cache.insert({1, {2}});
}
