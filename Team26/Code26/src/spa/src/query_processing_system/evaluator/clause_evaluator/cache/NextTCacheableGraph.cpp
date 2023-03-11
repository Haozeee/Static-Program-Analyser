#include "NextTCacheableGraph.h"

NextTCacheableGraph::NextTCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

std::unordered_map<int, std::unordered_set<int>> NextTCacheableGraph::getBase() {
    return storage->getNextManager()->getAllRelationshipEntries();
}
