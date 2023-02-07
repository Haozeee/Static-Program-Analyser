/*
#include "FollowsClauseEvaluator.h"
#include <unordered_map>
#include <string>
#include <iostream>

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> FollowsClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    ClauseArgumentTypes arg = getClauseArgumentTypes();
    if (arg == ClauseArgumentTypes::NUMBER_NUMBER) {
        evaluateNumberNumber(storage);
    } else if (arg == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    }

    return clauseResult;
}

void FollowsClauseEvaluator::evaluateNumberNumber(std::shared_ptr<ReadOnlyStorage> storage) {
    auto store = storage->getFollowsManager()->getAllRelationshipEntries();
    auto iterator = store.find(stoi(getLeftArg().getValue()));
    auto rightValue = stoi(getRightArg().getValue());
    */
/**
    std::cout << getLeftArg().getValue() << " " << getRightArg().getValue() << "\n";
    for (auto const& [k,v] : store) {
        std::cout << "key: " << k << " value: " << v << "\n";
    }
     *//*

    if (iterator == store.end() || !store.count(rightValue) ||iterator->second != rightValue) {
        std::cout << "Counting\n";
        clauseResult->setNoResults();
    }
}

void FollowsClauseEvaluator::evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage) {
    std::cout << "Not implemented\n";
}
*/
