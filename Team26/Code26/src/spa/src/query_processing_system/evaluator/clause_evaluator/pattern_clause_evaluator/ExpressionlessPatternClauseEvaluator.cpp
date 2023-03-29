#include "ExpressionlessPatternClauseEvaluator.h"
#include <utility>

ExpressionlessPatternClauseEvaluator::ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg)
        : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

void ExpressionlessPatternClauseEvaluator::evaluateSynonym() {
    auto statements = getRelationshipEntries();
    EntityEntityMap interestedResults = Util::intStringMapTostringMap(statements);
    clauseResultTable = ResultTable::createTableFromMap(interestedResults,
                                                        patternArg.getValue(), leftArg.getValue());
}

void ExpressionlessPatternClauseEvaluator::evaluateString() {
    auto relationshipStore = getReverseRelationshipEntries();
    auto it = relationshipStore.find(leftArg.getValue());
    EntitySet interestedResults;
    if (it != relationshipStore.end()) {
        interestedResults = Util::intSetToStringSet(it->second);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void ExpressionlessPatternClauseEvaluator::evaluateWildcard() {
    auto statements = getRelationshipEntries();
    EntitySet interestedResults = Util::intSetToStringSet(Util::getAllKeys(statements));
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}
