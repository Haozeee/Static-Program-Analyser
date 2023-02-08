#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <memory>
#include "clause_evaluator/ClauseResult.h"
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
    /**
     * The keys of the map should contain the identity in the select clauses.
     * The values are the results of the keys, represented as an unordered set.
     */
    ResultMap results;

 public:
    QueryResult();

    /**
     * Add a new identity that will be outputted in the result.
     * If identity already exists, ignore.
     * @param identity The identity to be added.
     */
    void addNewIdentity(std::string identity);

    /**
     * Add new results to an identity. This will override any existing results for the identity.
     * @param identity The identity whose results is to be updated.
     * @param toAdd The new results.
     */
    void addResultsToIdentity(std::string identity, std::unordered_set<std::string> toAdd);

    /**
     * Copy the query result into the qps results.
     * @param qpsResult The list containing the qps results, should be empty initially.
     */
    void copyToQpsResult(std::list<std::string> &qpsResult);

    /**
     * Apply the results from evaluating a clause to the query results. This is done
     * by finding the intersection of the relevant correct sets.
     * @param clauseResult The result of evaluating a particular clause.
     */
    void addClauseResultToQuery(std::shared_ptr<ClauseResult> clauseResult);

    bool operator ==(const QueryResult& other) const;

    friend std::ostream& operator << (std::ostream& os, const QueryResult& queryResult);
};


