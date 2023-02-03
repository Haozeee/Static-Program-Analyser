#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "../parser/SelectClause.h"

/**
 * Key: Identity of select clauses
 * Value: Set containing the results for that synonym
 */
using ResultMap = std::unordered_map<std::string, std::unordered_set<std::string>>;

/**
 * Stores the result of a query
 */
class QueryResult {
private:
    ResultMap results;

public:
    explicit QueryResult();

    /**
     * Add a new identity that will be outputted in the result.
     * If identity already exists, ignore.
     * @param identity The identity to be added.
     */
    void addNewIdentity(std::string identity);

    void addResultsToIdentity(std::string identity, std::unordered_set<std::string> toAdd);

    void addSingleResultToIdentity(std::string identity, std::string toAdd);

    bool operator ==(const QueryResult& other) const;

    friend std::ostream& operator << (std::ostream& os, const QueryResult& queryResult);
};


