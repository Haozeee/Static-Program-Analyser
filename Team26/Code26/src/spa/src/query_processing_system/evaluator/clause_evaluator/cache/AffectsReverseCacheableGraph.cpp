#include "AffectsReverseCacheableGraph.h"

AffectsReverseCacheableGraph::AffectsReverseCacheableGraph(StoragePointer storage)
    : AffectsBaseCacheableGraph(storage) {}

void AffectsReverseCacheableGraph::setBase() {
    base = storage->getNextManager()->getAllReversedRelationshipEntries();
}
