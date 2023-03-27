#include "NextTCacheableGraph.h"

NextTCacheableGraph::NextTCacheableGraph(CacheStorage storage) : TransitiveCacheableGraph(storage) {}

void NextTCacheableGraph::setBase() {
    base = StorageUtil::getRelationshipMap(storage->getNextManager());
}
