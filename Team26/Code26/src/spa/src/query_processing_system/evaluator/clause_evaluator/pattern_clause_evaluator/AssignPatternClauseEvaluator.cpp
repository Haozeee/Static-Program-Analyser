#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg), std::move(rightArg)) {}

void AssignPatternClauseEvaluator::evaluateSynonym() {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
    auto res = evaluateStringHelper(identities);
    clauseResultTable = ResultTable::createTableFromMap(res, patternArg.getValue(), leftArg.getValue());
}

void AssignPatternClauseEvaluator::evaluateString() {
    auto allResults = evaluateStringHelper({leftArg.getValue()});
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void AssignPatternClauseEvaluator::evaluateWildcard() {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, DesignEntity::VARIABLE);
    auto allResults = evaluateStringHelper(identities);
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

std::unordered_map<std::string, std::unordered_set<std::string>>
AssignPatternClauseEvaluator::evaluateStringHelper(std::unordered_set<std::string> lhsValues) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    auto assignStatements = storage->getAssignPatternManager()->getAllPatternEntries();
    auto lhsStatements = storage->getAssignPatternManager()->getAllLhsPatternEntries();
    auto rhsStatements = storage->getAssignPatternManager()->getAllRhsPatternEntries();
    for (auto const& [k, v] : assignStatements) {
        // k = index of assign statements
        // v actual position of assign statements in the source code
        auto lhs = lhsStatements->at(k);
        auto rhs = rhsStatements->at(k);
        if (lhsValues.count(lhs) && rightArg.matchesStatementTree(rhs)) {
            res.insert({std::to_string(v), {lhs}});
        }
    }
    return res;
}
