#include "TransitiveCacheableGraph.h"

TransitiveCacheableGraph::TransitiveCacheableGraph(StoragePointer storage) : CacheableGraph(storage) {}


std::unordered_set<int> TransitiveCacheableGraph::onCacheMiss(int query) {

}