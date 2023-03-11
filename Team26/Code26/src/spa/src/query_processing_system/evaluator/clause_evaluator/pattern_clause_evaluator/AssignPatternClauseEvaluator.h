#pragma once

#include <memory>
#include <variant>
#include <unordered_set>
#include <unordered_map>
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
    std::unordered_map<std::string, std::unordered_set<std::string>>
    evaluateStringHelper(std::unordered_set<std::string> lhsValues);

 public:
    AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);
};
