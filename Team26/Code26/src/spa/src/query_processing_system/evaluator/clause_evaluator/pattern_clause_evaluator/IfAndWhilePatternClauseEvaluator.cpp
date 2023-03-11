#include "IfAndWhilePatternClauseEvaluator.h"

#include <memory>
#include <utility>
#include <string>
#include <unordered_set>
#include <unordered_map>

IfAndWhilePatternClauseEvaluator::IfAndWhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
        : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

void IfAndWhilePatternClauseEvaluator::evaluateSynonym(std::shared_ptr<ReadStorage> storage) {
    auto ifOrWhileStatements = getRelationshipEntries(storage);
    std::unordered_map<std::string, std::unordered_set<std::string>> interestedResults
        = Util::intStringMapTostringMap(ifOrWhileStatements);
    clauseResultTable = ResultTable::createTableFromMap(interestedResults,
                                                        patternArg.getValue(), leftArg.getValue());
}

void IfAndWhilePatternClauseEvaluator::evaluateString(std::shared_ptr<ReadStorage> storage) {
    auto ifOrWhileStatements = getReverseRelationshipEntries(storage);
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : ifOrWhileStatements) {
        if (k == leftArg.getValue()) {
            interestedResults.insert(Util::intSetToStringSet(v).begin(),
                                     Util::intSetToStringSet(v).end());
        }
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void IfAndWhilePatternClauseEvaluator::evaluateWildcard(std::shared_ptr<ReadStorage> storage) {
    auto ifOrWhileStatements = getRelationshipEntries(storage);
    std::unordered_set<std::string> interestedResults
        = Util::intSetToStringSet(Util::getAllKeys(ifOrWhileStatements));
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}
