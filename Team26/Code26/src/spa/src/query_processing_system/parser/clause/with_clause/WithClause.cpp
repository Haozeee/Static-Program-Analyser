#include "WithClause.h"
#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/with_clause_evaluator/StringWithClauseEvaluator.h"
#include "query_processing_system/evaluator/clause_evaluator/with_clause_evaluator/IntWithClauseEvaluator.h"

WithClause::WithClause(Reference left, Reference right)
    : leftRef(std::move(left)), rightRef(std::move(right)) {}

bool WithClause::validateClause() {
    // Check if int int or string string
    auto check = (leftRef.isStringReference() && rightRef.isStringReference())
            || (leftRef.isIntReference() && rightRef.isIntReference());
    return check;
}

ClauseEvaluator* WithClause::getClauseEvaluator() {
    if (leftRef.isStringReference() && rightRef.isStringReference()) {
        return new StringWithClauseEvaluator(leftRef, rightRef);
    } else {
        return new IntWithClauseEvaluator(leftRef, rightRef);
    }
}

Reference WithClause::getLeftRef() {
    return this->leftRef;
}

Reference WithClause::getRightRef() {
    return this->rightRef;
}

bool WithClause::operator==(const WithClause& other) const {
    const WithClause* otherClause = dynamic_cast<const WithClause*>(&other);
    return otherClause != nullptr && this->leftRef == otherClause->leftRef && this->rightRef == otherClause->rightRef;
}