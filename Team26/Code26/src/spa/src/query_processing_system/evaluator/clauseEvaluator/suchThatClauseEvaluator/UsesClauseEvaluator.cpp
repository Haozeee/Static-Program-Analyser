#include "UsesClauseEvaluator.h"

UsesClauseEvaluator::UsesClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

bool UsesClauseEvaluator::evaluateClause() {
    return true;
}
