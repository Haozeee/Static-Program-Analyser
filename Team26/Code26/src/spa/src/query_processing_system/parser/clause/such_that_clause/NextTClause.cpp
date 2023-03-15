#include "NextTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/NextTClauseEvaluator.h"

NextTClause::NextTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* NextTClause::getClauseEvaluator() {
    return new NextTClauseEvaluator(getLeftArg(), getRightArg());
}
