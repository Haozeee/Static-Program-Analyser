#pragma once
#include "AffectsBaseCacheableGraph.h"

class AffectsReverseCacheableGraph : public AffectsBaseCacheableGraph {
 protected:
    void onCacheMiss(int startStatement) override;

 public:
    explicit AffectsReverseCacheableGraph(StoragePointer storage);

    void setBase() override;
};
