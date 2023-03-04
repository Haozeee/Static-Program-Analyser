#include "NextClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/NextClauseEvaluator.h"

NextClause::NextClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* NextClause::getClauseEvaluator() {
    return new NextClauseEvaluator(getLeftArg(), getRightArg());
}
