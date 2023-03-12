#include "NextTReverseCacheableGraph.h"

NextTReverseCacheableGraph::NextTReverseCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

void NextTReverseCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllReversedRelationshipEntries();
}
