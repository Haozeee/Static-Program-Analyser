#include "catch.hpp"
#include "query_processing_system/evaluator/UnionFind.h"

TEST_CASE("Union Items") {
    UnionFind unionFind;

    // Initially all items are disjoint
    unionFind.add("1");
    unionFind.add("2");
    unionFind.add("3");
    REQUIRE(unionFind.find("1") != unionFind.find("2"));
    REQUIRE(unionFind.find("2") != unionFind.find("3"));
    REQUIRE(unionFind.find("1") != unionFind.find("3"));

    // Union 1 and 3
    unionFind.unionItems("1", "3");
    REQUIRE(unionFind.find("1") == unionFind.find("3"));
    REQUIRE(unionFind.find("2") != unionFind.find("3"));

    // Union 2 and 4
    unionFind.unionItems("2", "4"); // Will implicitly add 4 since 4 does not exist
    REQUIRE(unionFind.find("2") == unionFind.find("4"));
    REQUIRE(unionFind.find("2") != unionFind.find("3"));
    REQUIRE(unionFind.find("2") != unionFind.find("1"));
    REQUIRE(unionFind.find("4") != unionFind.find("3"));
    REQUIRE(unionFind.find("4") != unionFind.find("1"));

    // Add additional item
    unionFind.add("5");

    // Union 2 and 3, now 1, 2, 3, 4 should be together
    unionFind.unionItems("2", "3");
    REQUIRE(unionFind.find("2") == unionFind.find("4"));
    REQUIRE(unionFind.find("2") == unionFind.find("3"));
    REQUIRE(unionFind.find("2") == unionFind.find("1"));
    REQUIRE(unionFind.find("4") == unionFind.find("3"));
    REQUIRE(unionFind.find("4") == unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("2"));
    REQUIRE(unionFind.find("5") != unionFind.find("3"));
    REQUIRE(unionFind.find("5") != unionFind.find("4"));
}

TEST_CASE("Union Multiple Items") {
    UnionFind unionFind;

    // Initially all items are disjoint
    unionFind.add("1");
    unionFind.add("2");
    unionFind.add("3");
    unionFind.add("4");
    unionFind.add("5");

    // Union 1, 2, 3, 4
    unionFind.unionMultipleItems({"1", "2", "3", "4"});
    REQUIRE(unionFind.find("2") == unionFind.find("4"));
    REQUIRE(unionFind.find("2") == unionFind.find("3"));
    REQUIRE(unionFind.find("2") == unionFind.find("1"));
    REQUIRE(unionFind.find("4") == unionFind.find("3"));
    REQUIRE(unionFind.find("4") == unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("2"));
    REQUIRE(unionFind.find("5") != unionFind.find("3"));
    REQUIRE(unionFind.find("5") != unionFind.find("4"));

    // Should do nothing
    unionFind.unionMultipleItems({});

    // Union 1 item, effectively does nothing
    unionFind.unionMultipleItems({"5"});
    REQUIRE(unionFind.find("2") == unionFind.find("4"));
    REQUIRE(unionFind.find("2") == unionFind.find("3"));
    REQUIRE(unionFind.find("2") == unionFind.find("1"));
    REQUIRE(unionFind.find("4") == unionFind.find("3"));
    REQUIRE(unionFind.find("4") == unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("1"));
    REQUIRE(unionFind.find("5") != unionFind.find("2"));
    REQUIRE(unionFind.find("5") != unionFind.find("3"));
    REQUIRE(unionFind.find("5") != unionFind.find("4"));
}
