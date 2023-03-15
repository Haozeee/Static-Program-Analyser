#include "AffectsTReverseCacheableGraph.h"

AffectsTReverseCacheableGraph::AffectsTReverseCacheableGraph(StoragePointer storage)
    : TransitiveCacheableGraph(storage) {}

void AffectsTReverseCacheableGraph::setBase(std::unordered_map<int, std::unordered_set<int>> newBase) {
    base = std::move(newBase);
}
