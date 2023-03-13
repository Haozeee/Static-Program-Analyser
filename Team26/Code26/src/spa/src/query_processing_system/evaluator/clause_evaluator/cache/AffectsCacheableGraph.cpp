#include "AffectsCacheableGraph.h"

AffectsCacheableGraph::AffectsCacheableGraph(StoragePointer storage) : AffectsBaseCacheableGraph(storage) {}

void AffectsCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllRelationshipEntries();
}
