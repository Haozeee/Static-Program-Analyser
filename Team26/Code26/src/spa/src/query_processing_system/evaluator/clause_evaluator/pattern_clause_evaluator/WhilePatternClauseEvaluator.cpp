#include "WhilePatternClauseEvaluator.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                                         StringExpression rightArg)
    : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg),
                             StringExpression(true)) {}

std::shared_ptr<ResultTable> WhilePatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadStorage> storage) {
    auto leftArgType = leftArg.getArgumentType();
    if (leftArgType == ArgumentType::SYNONYM) {
        evaluateSynonym(storage);
    } else if (leftArgType == ArgumentType::CHARACTERSTRING) {
        evaluateString(storage);
    } else if (leftArgType == ArgumentType::WILDCARD) {
        evaluateWildcard(storage);
    } else {
        // Not a valid pattern clause
        throw std::exception();
    }

    optimiseResults();
    return clauseResultTable;
}

void WhilePatternClauseEvaluator::evaluateSynonym(std::shared_ptr<ReadStorage> storage) {
    auto whileStatements = storage->getWhileCondManager()->getAllRelationshipEntries();
    std::unordered_map<std::string, std::unordered_set<std::string>> interestedResults;
    for (auto const& [k, v] : whileStatements) {
        interestedResults[std::to_string(k)] = v;
    }
    clauseResultTable = ResultTable::createTableFromMap(interestedResults, patternArg.getValue(), leftArg.getValue());
}

void WhilePatternClauseEvaluator::evaluateString(std::shared_ptr<ReadStorage> storage) {
    auto whileStatements = storage->getWhileCondManager()->getAllRelationshipEntries();
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : whileStatements) {
        if (v.count(leftArg.getValue())) {
            interestedResults.insert(std::to_string(k));
        }
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void WhilePatternClauseEvaluator::evaluateWildcard(std::shared_ptr<ReadStorage> storage) {
    auto whileStatements = storage->getWhileCondManager()->getAllRelationshipEntries();
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : whileStatements) {
        interestedResults.insert(std::to_string(k));
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}
