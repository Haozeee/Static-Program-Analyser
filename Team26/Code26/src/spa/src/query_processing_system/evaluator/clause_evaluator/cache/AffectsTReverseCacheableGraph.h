#pragma once
#include "TransitiveCacheableGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <utility>

class AffectsTReverseCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit AffectsTReverseCacheableGraph(CacheStorage storage);

    void setBase(StmtStmtMap newBase);
};
