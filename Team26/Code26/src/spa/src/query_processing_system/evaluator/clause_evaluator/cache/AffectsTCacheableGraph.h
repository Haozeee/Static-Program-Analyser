#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "TransitiveCacheableGraph.h"

class AffectsTCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit AffectsTCacheableGraph(StoragePointer storage);

    void setBase(std::unordered_map<int, std::unordered_set<int>> newBase);
};
