#pragma once
#include "TransitiveCacheableGraph.h"
#include <unordered_map>
#include <unordered_set>

class NextTCacheableGraph : public TransitiveCacheableGraph {
 protected:
    virtual std::unordered_map<int, std::unordered_set<int>> getBase() override;

 public:
    NextTCacheableGraph(StoragePointer storage);
};
