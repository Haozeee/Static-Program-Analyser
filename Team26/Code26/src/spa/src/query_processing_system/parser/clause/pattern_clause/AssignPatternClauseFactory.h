#pragma once

#include "AssignPatternClause.h"
#include "PatternClauseFactory.h"
#include "query_processing_system/parser/Synonym.h"

class AssignPatternClauseFactory : public PatternClauseFactory {
 public:
    /**
     * Factory method to create a new Assign Pattern Clause.
     *
     * @param designEntity The Design Entity of the pattern clause: ASSIGN, IF, WHILE
     * @param leftArg The left argument for the clause.
     * @param rightArg The right argument for the clause.
     * @return The AssignPatternClause object.
     */
    PatternClause* createPatternClause(DesignEntity designEntity, Argument leftArg, StringExpression rightArg);
};
