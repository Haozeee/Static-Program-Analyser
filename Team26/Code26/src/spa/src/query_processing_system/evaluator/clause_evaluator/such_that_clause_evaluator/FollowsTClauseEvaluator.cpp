#include "FollowsTClauseEvaluator.h"
#include <unordered_map>

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

}

void FollowsTClauseEvaluator::evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage) {

}