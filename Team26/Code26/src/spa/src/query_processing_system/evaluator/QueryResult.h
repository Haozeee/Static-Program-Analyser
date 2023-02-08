#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <memory>
#include "Result.h"
#include "PkbUtil.h"
#include "clause_evaluator/ClauseResult.h"
#include "../parser/SelectClause.h"

/**
 * Stores the result of a query
 */
class QueryResult : public Result {
 public:
    QueryResult();

    /**
     * Add a new identity that will be outputted in the result.
     * If identity already exists, ignore.
     * @param identity The identity to be added.
     */
    void addNewIdentity(std::string identity);

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
};
