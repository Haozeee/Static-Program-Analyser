#include "catch.hpp"
#include "query_processing_system/evaluator/clause_evaluator/cache/TransitiveCacheableGraph.h"

StmtStmtMap mockBase {
        {1, {2, 3}},
        {2, {4}},
        {3, {5}},
        {4, {6}}
};

class MockGraph : public TransitiveCacheableGraph {
 public:
    MockGraph() : TransitiveCacheableGraph(nullptr) {}

    void setBase() override {
        base = mockBase;
    }
};

TEST_CASE("Test Transitive Graph") {
    MockGraph mockGraph = MockGraph();
    mockGraph.setBase();

    StmtSet toInsert;
    StmtStmtMap cacheData;
    StmtSet expectedResults;

    // Initially cache is empty
    REQUIRE(mockGraph.getCacheData().empty());

    // Inserting nothing into the cache
    mockGraph.insertItemsIntoCache(toInsert);
    REQUIRE(mockGraph.getCacheData().empty());

    // Insert 1 to cache
    toInsert = {1};
    mockGraph.insertItemsIntoCache(toInsert);
    cacheData = mockGraph.getCacheData();
    // The cache should only contain the value 1
    REQUIRE(cacheData.size() == 1);
    REQUIRE(cacheData.count(1));
    expectedResults = {2, 3, 4, 5, 6};
    REQUIRE(cacheData.at(1) == expectedResults);

    toInsert = {3};
    mockGraph.insertItemsIntoCache(toInsert);
    cacheData = mockGraph.getCacheData();
    // The graph should now contain the value 3
    REQUIRE(cacheData.count(3));
    expectedResults = {5};
    REQUIRE(cacheData.at(3) == expectedResults);
}
