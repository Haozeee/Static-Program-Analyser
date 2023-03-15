#pragma once
#include "TransitiveCacheableGraph.h"
#include <unordered_map>
#include <unordered_set>

class NextTCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit NextTCacheableGraph(StoragePointer storage);

    void setBase() override;
};
