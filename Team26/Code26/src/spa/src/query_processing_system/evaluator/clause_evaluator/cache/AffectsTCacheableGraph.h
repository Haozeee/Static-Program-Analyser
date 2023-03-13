#include "TransitiveCacheableGraph.h"
#include <unordered_map>
#include <unordered_set>

class AffectsTCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit AffectsTCacheableGraph(StoragePointer storage);

    void setBase(std::unordered_map<int, std::unordered_set<int>> newBase);
};
