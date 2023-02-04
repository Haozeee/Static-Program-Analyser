#include "UsesClause.h"
#include <utility>
#include "../../../evaluator/clauseEvaluator/suchThatClauseEvaluator/UsesClauseEvaluator.h"

UsesClause::UsesClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesClause::getClauseEvaluator() {
    return new UsesClauseEvaluator(getLeftArg(), getRightArg());
}
