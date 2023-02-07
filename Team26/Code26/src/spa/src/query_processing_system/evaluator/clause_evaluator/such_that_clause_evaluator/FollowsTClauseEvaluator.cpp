#include "FollowsTClauseEvaluator.h"
#include <unordered_map>
#include <string>
#include <iostream>

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> FollowsTClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    ClauseArgumentTypes arg = getClauseArgumentTypes();
    if (arg == ClauseArgumentTypes::NUMBER_NUMBER) {
        evaluateNumberNumber(storage);
    } else if (arg == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    }

    return clauseResult;
}

void FollowsTClauseEvaluator::evaluateNumberNumber(std::shared_ptr<ReadOnlyStorage> storage) {
    auto store = storage->getFollowsManager()->getAllRelationshipEntries();
    auto iterator = store.find(stoi(getLeftArg().getValue()));
    auto rightValue = stoi(getRightArg().getValue());
    /**
    std::cout << getLeftArg().getValue() << " " << getRightArg().getValue() << "\n";
    for (auto const& [k,v] : store) {
        std::cout << "key: " << k << " value: " << v << "\n";
    }
     */
    if (iterator == store.end() || !store.count(rightValue) ||iterator->second != rightValue) {
        std::cout << "Counting\n";
        clauseResult->setNoResults();
    }
}

void FollowsTClauseEvaluator::evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage) {
    std::cout << "Not implemented\n";
}