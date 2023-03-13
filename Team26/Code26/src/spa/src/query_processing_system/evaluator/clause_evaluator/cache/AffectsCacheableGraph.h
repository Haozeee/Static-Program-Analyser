#pragma once
#include "AffectsBaseCacheableGraph.h"

class AffectsCacheableGraph : public AffectsBaseCacheableGraph {
 public:
    explicit AffectsCacheableGraph(StoragePointer storage);

    void setBase() override;
};
