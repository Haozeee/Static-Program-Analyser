#include "NextTReverseCacheableGraph.h"

NextTReverseCacheableGraph::NextTReverseCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

std::unordered_map<int, std::unordered_set<int>> NextTReverseCacheableGraph::getBase() {
    return storage->getNextManager()->getAllReversedRelationshipEntries();
}