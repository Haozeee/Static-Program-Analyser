#pragma once
#include "AffectsBaseCacheableGraph.h"

class AffectsCacheableGraph : public AffectsBaseCacheableGraph {
 protected:
    void onCacheMiss(int startStatement) override;

 public:
    explicit AffectsCacheableGraph(StoragePointer storage);

    void setBase() override;
};
