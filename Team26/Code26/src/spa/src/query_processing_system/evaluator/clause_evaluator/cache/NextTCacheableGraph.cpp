#include "NextTCacheableGraph.h"

NextTCacheableGraph::NextTCacheableGraph(ProgrammeStore storage) : TransitiveCacheableGraph(storage) {}

void NextTCacheableGraph::setBase() {
    base = StorageUtil::getRelationshipMap(storage->getNextManager());
}
