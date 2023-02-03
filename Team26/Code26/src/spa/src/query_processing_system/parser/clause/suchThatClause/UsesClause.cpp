#include "UsesClause.h"
#include "../../../evaluator/clauseEvaluator/suchThatClauseEvaluator/UsesClauseEvaluator.h"

ClauseEvaluator* UsesClause::getClauseEvaluator() {
    return new UsesClauseEvaluator(getLeftArg(), getRightArg());
}
