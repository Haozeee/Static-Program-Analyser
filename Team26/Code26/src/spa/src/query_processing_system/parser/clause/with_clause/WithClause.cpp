#include "WithClause.h"
#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/with_clause_evaluator/StringWithClauseEvaluator.h"
#include "query_processing_system/evaluator/clause_evaluator/with_clause_evaluator/IntWithClauseEvaluator.h"

WithClause::WithClause(Reference left, Reference right)
    : leftRef(std::move(left)), rightRef(std::move(right)) {}

bool WithClause::validateClause() {
    // Check if int int or string string
    auto check = (leftRef.isStringReference() && rightRef.isStringReference())
            || (leftRef.isIntReference() && rightRef.isStringReference());
    return check;
}

ClauseEvaluator* WithClause::getClauseEvaluator() {
    if (leftRef.isStringReference() && rightRef.isStringReference()) {
        return new StringWithClauseEvaluator(leftRef, rightRef);
    } else {
        return new IntWithClauseEvaluator(leftRef, rightRef);
    }
}
