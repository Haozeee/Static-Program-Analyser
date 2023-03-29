#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg), std::move(rightArg)) {}

void AssignPatternClauseEvaluator::evaluateSynonym() {
    auto identities = storage->getStringEntitiesFromPkb(leftArg.getDesignEntity());
    auto res = evaluateStringHelper(identities);
    clauseResultTable = ResultTable::createTableFromMap(res, patternArg.getValue(), leftArg.getValue());
}

void AssignPatternClauseEvaluator::evaluateString() {
    auto allResults = evaluateStringHelper({leftArg.getValue()});
    EntitySet interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void AssignPatternClauseEvaluator::evaluateWildcard() {
    auto identities = storage->getStringEntitiesFromPkb(DesignEntity::VARIABLE);
    auto allResults = evaluateStringHelper(identities);
    EntitySet interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

EntityEntityMap AssignPatternClauseEvaluator::evaluateStringHelper(EntitySet lhsValues) {
    EntityEntityMap res;

    auto assignStatements = storage->getAssignStatementEntries(lhsValues);
    for (auto const& [k, v] : assignStatements) {
        // lhs = left side of the assign statement
        // rhs = right side of the assign statement
        auto lhs = v.first;
        auto rhs = v.second;
        if (lhsValues.count(lhs) && rightArg.matchesStatementTree(rhs)) {
            res.insert({std::to_string(k), {lhs}});
        }
    }
    return res;
}
