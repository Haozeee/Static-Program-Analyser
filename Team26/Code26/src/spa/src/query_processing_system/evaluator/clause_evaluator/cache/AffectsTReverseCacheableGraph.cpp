#include "AffectsTReverseCacheableGraph.h"

AffectsTReverseCacheableGraph::AffectsTReverseCacheableGraph(ProgrammeStore storage)
    : TransitiveCacheableGraph(storage) {}

void AffectsTReverseCacheableGraph::setBase(StmtStmtMap newBase) {
    base = std::move(newBase);
}
