#include "AffectsTCacheableGraph.h"

AffectsTCacheableGraph::AffectsTCacheableGraph(StoragePointer storage) : TransitiveCacheableGraph(storage) {}

void AffectsTCacheableGraph::setBase(std::unordered_map<int, std::unordered_set<int>> newBase) {
    base = std::move(newBase);
}
