#include "ExpressionlessPatternClauseEvaluator.h"

#include <memory>
#include <utility>
#include <unordered_set>
#include <unordered_map>

ExpressionlessPatternClauseEvaluator::ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg)
        : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

void ExpressionlessPatternClauseEvaluator::evaluateSynonym() {
    auto statements = getRelationshipEntries();
    std::unordered_map<std::string, std::unordered_set<std::string>> interestedResults
        = Util::intStringMapTostringMap(statements);
    clauseResultTable = ResultTable::createTableFromMap(interestedResults,
                                                        patternArg.getValue(), leftArg.getValue());
}

void ExpressionlessPatternClauseEvaluator::evaluateString() {
    auto relationshipStore = getReverseRelationshipEntries();
    auto it = relationshipStore.find(leftArg.getValue());
    std::unordered_set<std::string> interestedResults;
    if (it != relationshipStore.end()) {
        interestedResults = Util::intSetToStringSet(it->second);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void ExpressionlessPatternClauseEvaluator::evaluateWildcard() {
    auto statements = getRelationshipEntries();
    std::unordered_set<std::string> interestedResults
        = Util::intSetToStringSet(Util::getAllKeys(statements));
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}
