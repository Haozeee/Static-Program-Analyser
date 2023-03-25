#include "NextTReverseCacheableGraph.h"

NextTReverseCacheableGraph::NextTReverseCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

void NextTReverseCacheableGraph::setBase() {
    base = StorageUtil::getReverseRelationshipMap(storage->getNextManager());
}
