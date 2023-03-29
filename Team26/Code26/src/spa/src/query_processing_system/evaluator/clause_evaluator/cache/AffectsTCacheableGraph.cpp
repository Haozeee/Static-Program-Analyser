#include "AffectsTCacheableGraph.h"

AffectsTCacheableGraph::AffectsTCacheableGraph(CacheStorage storage) : TransitiveCacheableGraph(storage) {}

void AffectsTCacheableGraph::setBase(StmtStmtMap newBase) {
    base = std::move(newBase);
}
