#include "AffectsTCacheableGraph.h"

AffectsTCacheableGraph::AffectsTCacheableGraph(ProgrammeStore storage) : TransitiveCacheableGraph(storage) {}

void AffectsTCacheableGraph::setBase(StmtStmtMap newBase) {
    base = std::move(newBase);
}
