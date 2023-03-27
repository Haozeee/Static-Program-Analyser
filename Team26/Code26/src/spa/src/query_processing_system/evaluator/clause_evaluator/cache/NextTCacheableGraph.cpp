#include "NextTCacheableGraph.h"

NextTCacheableGraph::NextTCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

void NextTCacheableGraph::setBase() {
    base = StorageUtil::getRelationshipMap(storage->getNextManager());
}
