#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "TransitiveCacheableGraph.h"

class AffectsTCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit AffectsTCacheableGraph(ProgrammeStore storage);

    void setBase(StmtStmtMap newBase);
};
