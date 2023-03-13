#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "CacheableGraph.h"
#include "../../Util.h"

class AffectsBaseCacheableGraph : public CacheableGraph<int, int> {
 protected:
    std::unordered_map<int, std::unordered_set<std::string>> modifiesMap;

    std::unordered_map<int, std::unordered_set<std::string>> usesMap;

    std::unordered_set<int> assignStatements;

    std::unordered_set<int> readStatements;

    std::unordered_set<int> callStatements;

    explicit AffectsBaseCacheableGraph(StoragePointer storage);

    bool isReadCallOrAssign(int stmt);

    /**
     * Given a stmt, get all the variables modified by this statement.
     * Should only be used for assign, read or call statements.
     */
    std::string modifiesVariable(int stmt);

 public:
    bool isEmpty() override;

    /**
     * Complete building the entire graph.
     */
    void buildAll();
};
