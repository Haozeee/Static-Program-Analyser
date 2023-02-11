#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

/**
 * Key: Identity of select clauses
 * Value: Set containing the results for that synonym
 */
using ResultMap = std::unordered_map<std::string, std::unordered_set<std::string>>;

class Result {
 protected:
    /**
    * The keys of the map should contain the an identity.
    * The values are the results of the keys, represented as an unordered set of string.
    */
    ResultMap results;

 public:
    /**
     * Add a new result to a key. This replaces any exising results mapped to the key.
     * @param key The key to assign the results to.
     * @param toAdd The results.
     */
    void addNewResult(std::string key, std::unordered_set<std::string> toAdd);

    /**
     * Add a new result to a key by doing a union with any existing values. Existing results are
     * not overridden.
     * @param key The key to assign the results to.
     * @param toUnion The results to union.
     */
    void unionResult(std::string key, std::unordered_set<std::string> toUnion);

    ResultMap getResults();

    friend std::ostream& operator <<(std::ostream& os, const Result& result);
};
