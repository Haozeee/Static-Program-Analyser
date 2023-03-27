#include "AffectsTReverseCacheableGraph.h"

AffectsTReverseCacheableGraph::AffectsTReverseCacheableGraph(CacheStorage storage)
    : TransitiveCacheableGraph(storage) {}

void AffectsTReverseCacheableGraph::setBase(StmtStmtMap newBase) {
    base = std::move(newBase);
}
