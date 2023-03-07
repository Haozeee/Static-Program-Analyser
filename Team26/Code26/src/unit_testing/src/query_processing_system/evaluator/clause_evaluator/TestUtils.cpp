#include "catch.hpp"
#include "query_processing_system/evaluator/Util.h"
#include <unordered_set>
#include <unordered_map>
#include <string>

using IntSet = std::unordered_set<int>;
using StringSet = std::unordered_set<std::string>;
using IntMapSet = std::unordered_map<int, std::unordered_set<int>>;

IntSet setA = {1, 2, 3, 4, 5};
IntSet setB = {3, 4, 5, 6, 7};
IntMapSet mapA = {
        {1, {2, 3, 4}},
        {3, {4, 6}},
        {8, {9}}
};

TEST_CASE("Test Int Set To String Set") {
    IntSet intSet {1, 2, 3};
    StringSet stringSet {"1", "2", "3"};
    REQUIRE(stringSet == Util::intSetToStringSet(intSet));

    // Empty set
    intSet = {};
    stringSet = {};
    REQUIRE(stringSet == Util::intSetToStringSet(intSet));
}

TEST_CASE("Test Int Map To String Map") {
    std::unordered_map<int, IntSet> intMap {
            {1, {2, 4}},
            {5, {6}}
    };
    std::unordered_map<std::string, StringSet> stringMap {
            {"1", {"2", "4"}},
            {"5", {"6"}}
    };
    REQUIRE(stringMap == Util::intMapTostringMap(intMap));
}

TEST_CASE("Test Set Intersection") {
    IntSet res;
    Util::setIntersection(setA, setB, res);
    IntSet expectedRes {3, 4, 5};
    REQUIRE(res == expectedRes);

    // Intersection with empty set
    res = {};
    expectedRes = {};
    Util::setIntersection(setA, {}, res);
    REQUIRE(res == expectedRes);
    res = {};
    Util::setIntersection({}, setA, res);
    REQUIRE(res == expectedRes);
}

TEST_CASE("Test Set Union") {
    IntSet set1 = setA;
    IntSet set2 = setB;
    Util::setUnion(set1, set2);
    IntSet expectedRes {1, 2, 3, 4, 5, 6, 7};
    REQUIRE(set1 == expectedRes);

    // Union with empty set
    set1 = setA;
    Util::setUnion(set1, {});
    REQUIRE(set1 == setA);
    set1 = {};
    Util::setUnion(set1, setB);
    REQUIRE(set1 == setB);
}

TEST_CASE("Test Filter Map") {
    IntSet searchKeys {3, 8};
    auto res = Util::filterMap(mapA, searchKeys);
    IntMapSet expected {
            {3, {4, 6}},
            {8, {9}}
    };
    REQUIRE(expected == res);

    // Empty search keys
    searchKeys = {};
    res = Util::filterMap(mapA, searchKeys);
    expected = {};
    REQUIRE(res == expected);
}

TEST_CASE("Test Map Set Intersection") {
    auto res = Util::mapSetIntersection(mapA, setA);
    std::unordered_map<int, IntSet> expectedRes {
            {1, {2, 3, 4}},
            {3, {4}}
    };
    REQUIRE(res == expectedRes);
}
