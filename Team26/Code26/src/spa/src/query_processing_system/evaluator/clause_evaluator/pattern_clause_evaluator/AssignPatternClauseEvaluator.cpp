#include "AssignPatternClauseEvaluator.h"

#include <utility>

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg), std::move(rightArg)) {}

std::shared_ptr<ResultTable> AssignPatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
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

    return clauseResultTable;
}

void AssignPatternClauseEvaluator::evaluateSynonym(std::shared_ptr<ReadOnlyStorage> storage) {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
    auto res = evaluateStringHelper(storage, identities);
    clauseResultTable = ResultTable::createDoubleColumnTable(patternArg.getValue(), res.first,
                                                             leftArg.getValue(), res.second);
}

void AssignPatternClauseEvaluator::evaluateString(std::shared_ptr<ReadOnlyStorage> storage) {
    auto res = evaluateStringHelper(storage, {leftArg.getValue()});
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), res.first);
}

void AssignPatternClauseEvaluator::evaluateWildcard(std::shared_ptr<ReadOnlyStorage> storage) {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, DesignEntity::VARIABLE);
    auto res = evaluateStringHelper(storage, identities);
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), res.first);
}

std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
AssignPatternClauseEvaluator::evaluateStringHelper(std::shared_ptr<ReadOnlyStorage> storage,
                                                   std::unordered_set<std::string> lhsValues) {
    std::unordered_set<std::string> assignResults;
    std::unordered_set<std::string> lhsResults;
    auto assignStatements = storage->getPatternManager()->getAllPatternEntries();
    auto lhsStatements = storage->getPatternManager()->getAllLhsPatternEntries();
    auto rhsStatements = storage->getPatternManager()->getAllRhsPatternEntries();
    for (auto const& [k, v] : assignStatements) {
        // k = index of assign statements
        // v actual position of assign statements in the source code
        std::string lhs = lhsStatements.at(k);
        std::string rhs = rhsStatements.at(k);
        if (lhsValues.count(lhs) && rightArg.matchesString(rhs)) {
            assignResults.insert(std::to_string(v));
            lhsResults.insert(lhs);
        }
    }
    return std::make_pair(assignResults, lhsResults);
}
