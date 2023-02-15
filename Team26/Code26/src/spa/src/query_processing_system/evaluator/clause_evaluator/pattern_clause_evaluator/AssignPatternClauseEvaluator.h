#pragma once

#include <memory>
#include <variant>
#include <unordered_set>
#include <string>
#include <utility>
#include "PatternClauseEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    /**
     * Evaluates pattern clauses of the form pattern a(v, "x")
     */
    void evaluateSynonym(std::shared_ptr<ReadOnlyStorage> storage);

    /**
     * Evaluates pattern clauses of the form pattern a("y", "x")
     */
    void evaluateString(std::shared_ptr<ReadOnlyStorage> storage);

    /**
     * Evaluates pattern clauses of the form pattern a(_, "x")
     */
    void evaluateWildcard(std::shared_ptr<ReadOnlyStorage> storage);

    /**
     * Given a set of lhs values, find all the assign statements that have any of the lhs values
     * on the left side and whose right side matches the string expression argument.
     * @return A pair containing the set of matching assign statements and another set with the
     * lhs values that has matches.
     */
    std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
    evaluateStringHelper(std::shared_ptr<ReadOnlyStorage> storage, std::unordered_set<std::string> lhsValues);

 public:
    AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);

    std::shared_ptr<ResultTable> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
