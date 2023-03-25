#pragma once

#include <memory>
#include <string>
#include <utility>
#include "PatternClauseEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    /**
     * Evaluates pattern clauses of the form pattern a(v, "x")
     */
    void evaluateSynonym() override;

    /**
     * Evaluates pattern clauses of the form pattern a("y", "x")
     */
    void evaluateString() override;

    /**
     * Evaluates pattern clauses of the form pattern a(_, "x")
     */
    void evaluateWildcard() override;

    /**
     * Given a set of lhs values, find all the assign statements that have any of the lhs values
     * on the left side and whose right side matches the string expression argument.
     * @return A map with keys as the assign statements and values as the lhs values.
     */
    EntityEntityMap evaluateStringHelper(EntitySet lhsValues);

 public:
    AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);
};
