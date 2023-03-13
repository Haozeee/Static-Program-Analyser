#pragma once
#include "AffectsBaseCacheableGraph.h"

class AffectsReverseCacheableGraph : public AffectsBaseCacheableGraph {
 public:
    explicit AffectsReverseCacheableGraph(StoragePointer storage);

    void setBase() override;
};
