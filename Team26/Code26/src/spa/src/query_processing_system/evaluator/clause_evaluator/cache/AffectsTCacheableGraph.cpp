#include "AffectsTCacheableGraph.h"

AffectsTCacheableGraph::AffectsTCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

void AffectsTCacheableGraph::setBase(StmtStmtCache newBase) {
    base = std::move(newBase);
}
