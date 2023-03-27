#include "NextTReverseCacheableGraph.h"

NextTReverseCacheableGraph::NextTReverseCacheableGraph(CacheStorage storage) : TransitiveCacheableGraph(storage) {}

void NextTReverseCacheableGraph::setBase() {
    base = StorageUtil::getReverseRelationshipMap(storage->getNextManager());
}
