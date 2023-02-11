#pragma once

#include "AssignPatternClause.h"
#include "PatternClauseFactory.h"

class AssignPatternClauseFactory : public PatternClauseFactory {
 public:
    /**
     * Factory method to create a new Assign Pattern Clause.
     *
     * @param leftArg The left argument for the clause.
     * @param rightArg The right argument for the clause.
     * @return The AssignPatternClause object.
     */
    PatternClause* createPatternClause(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg);
};
