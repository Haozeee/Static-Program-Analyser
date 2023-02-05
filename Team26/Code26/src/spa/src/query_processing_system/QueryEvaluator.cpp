#include "QueryEvaluator.h"
#include <algorithm>
#include "evaluator/QueryResult.h"

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage)
    : query(query), storage(storage) {}

QueryResult QueryEvaluator::evaluateQuery() {
    // Evaluate select clauses
    evaluateSelectClause();

    // Get filters

    // Apply filters to result

    // Return QueryResult
    return queryResult;
}

void QueryEvaluator::evaluateSelectClause() {
    auto selectClauses = query->getSelectClause()->getSelectClauseItems();
    // Loop through select clauses
    for (SelectClauseItem item : *selectClauses) {
        std::shared_ptr<Synonym> syn = std::get<std::shared_ptr<Synonym>>(item);
        // Add identity to results
        queryResult.addNewIdentity(syn->ident);
        // Get respective entities from pkb
        auto entities = getEntitiesFromPkb(query->getSynonymDesignEntity(syn));
        // Add entities to query result
        queryResult.addResultsToIdentity(syn->ident, entities);
    }
}

/**
 * Converts a set containing integers to a set of strings.
 * @param intSet The set to be converted.
 * @return The string set.
 */
static std::unordered_set<std::string> intSetToStringSet(std::unordered_set<int> intSet) {
    std::unordered_set<std::string> result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}

std::unordered_set<std::string> QueryEvaluator::getEntitiesFromPkb(DesignEntity entity) {
    switch (entity) {
        case DesignEntity::VARIABLE:
            return storage->getVariableManager()->getAllEntitiesEntries();
        case DesignEntity::ASSIGN:
            return intSetToStringSet(storage->getAssignManager()->getAllEntitiesEntries());
        case DesignEntity::STMT:
            return intSetToStringSet(storage->getStmtManager()->getAllEntitiesEntries());
        case DesignEntity::PROCEDURE:
            return storage->getProcedureManager()->getAllEntitiesEntries();
        case DesignEntity::NONE:
            return {};
    }
}
