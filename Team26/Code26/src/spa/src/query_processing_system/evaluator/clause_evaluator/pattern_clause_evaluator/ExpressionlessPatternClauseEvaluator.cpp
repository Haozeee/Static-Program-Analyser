#include "ExpressionlessPatternClauseEvaluator.h"

#include <memory>
#include <utility>
#include <string>
#include <unordered_set>
#include <unordered_map>

ExpressionlessPatternClauseEvaluator::ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg)
        : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

void ExpressionlessPatternClauseEvaluator::evaluateSynonym(std::shared_ptr<ReadStorage> storage) {
    auto statements = getRelationshipEntries(storage);
    std::unordered_map<std::string, std::unordered_set<std::string>> interestedResults
        = Util::intStringMapTostringMap(statements);
    clauseResultTable = ResultTable::createTableFromMap(interestedResults,
                                                        patternArg.getValue(), leftArg.getValue());
}

void ExpressionlessPatternClauseEvaluator::evaluateString(std::shared_ptr<ReadStorage> storage) {
    auto relationshipStore = getReverseRelationshipEntries(storage);
    auto it = relationshipStore.find(leftArg.getValue());
    std::unordered_set<std::string> interestedResults;
    if (it != relationshipStore.end()) {
        interestedResults = Util::intSetToStringSet(it->second);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void ExpressionlessPatternClauseEvaluator::evaluateWildcard(std::shared_ptr<ReadStorage> storage) {
    auto statements = getRelationshipEntries(storage);
    std::unordered_set<std::string> interestedResults
        = Util::intSetToStringSet(Util::getAllKeys(statements));
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}
