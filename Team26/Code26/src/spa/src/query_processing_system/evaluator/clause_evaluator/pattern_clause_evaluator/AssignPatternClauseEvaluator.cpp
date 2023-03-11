#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(std::move(patternArg), std::move(leftArg), std::move(rightArg)) {}

std::shared_ptr<ResultTable> AssignPatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadStorage> storage) {
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

void AssignPatternClauseEvaluator::evaluateSynonym(std::shared_ptr<ReadStorage> storage) {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
    auto res = evaluateStringHelper(storage, identities);
    clauseResultTable = ResultTable::createTableFromMap(res, patternArg.getValue(), leftArg.getValue());
}

void AssignPatternClauseEvaluator::evaluateString(std::shared_ptr<ReadStorage> storage) {
    auto allResults = evaluateStringHelper(storage, {leftArg.getValue()});
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

void AssignPatternClauseEvaluator::evaluateWildcard(std::shared_ptr<ReadStorage> storage) {
    auto identities = PkbUtil::getStringEntitiesFromPkb(storage, DesignEntity::VARIABLE);
    auto allResults = evaluateStringHelper(storage, identities);
    std::unordered_set<std::string> interestedResults;
    for (auto const& [k, v] : allResults) {
        interestedResults.insert(k);
    }
    clauseResultTable = ResultTable::createSingleColumnTable(patternArg.getValue(), interestedResults);
}

std::unordered_map<std::string, std::unordered_set<std::string>>
AssignPatternClauseEvaluator::evaluateStringHelper(std::shared_ptr<ReadStorage> storage,
                                                   std::unordered_set<std::string> lhsValues) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    auto assignStatements = storage->getPatternManager()->getAllPatternEntries();
    auto lhsStatements = storage->getPatternManager()->getAllLhsPatternEntries();
    auto rhsStatements = storage->getPatternManager()->getAllRhsPatternEntries();
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
