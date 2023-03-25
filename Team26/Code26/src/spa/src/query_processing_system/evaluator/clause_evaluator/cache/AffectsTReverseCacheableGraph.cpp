#include "AffectsTReverseCacheableGraph.h"

AffectsTReverseCacheableGraph::AffectsTReverseCacheableGraph(StoragePointer storage)
    : TransitiveCacheableGraph(storage) {}

void AffectsTReverseCacheableGraph::setBase(StmtStmtCache newBase) {
    base = std::move(newBase);
}
