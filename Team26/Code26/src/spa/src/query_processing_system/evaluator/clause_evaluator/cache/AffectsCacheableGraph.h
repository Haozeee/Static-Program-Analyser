#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "../../Util.h"
#include "CacheableGraph.h"

class AffectsCacheableGraph : public CacheableGraph<int, int> {
 private:
    std::unordered_map<int, std::unordered_set<std::string>> modifiesMap;

    std::unordered_map<int , std::unordered_set<std::string>> callsSMap;

    std::unordered_map<int, std::unordered_set<std::string>> usesMap;

    std::unordered_set<int> assignStatements;

    std::unordered_set<int> readStatements;

    std::unordered_set<int> callStatements;

    IntIntCache reverseCache;

    bool fullyBuilt = false;

    bool callStatementModifiesVariable(int callStatement, std::string variableModified);

    bool isReadOrAssign(int stmt);

    /**
     * Given a stmt, get all the variables modified by this statement.
     * Should only be used for assign, read or call statements.
     */
    std::string modifiesVariable(int stmt);

 protected:
    void onCacheMiss(int query) override;

 public:
    explicit AffectsCacheableGraph(StoragePointer storage);

    void setBase() override;

    bool isEmpty() override;

    /**
     * Complete building the entire graph.
     */
    void buildAll() override;

    IntIntCache getReverseCache();
};
