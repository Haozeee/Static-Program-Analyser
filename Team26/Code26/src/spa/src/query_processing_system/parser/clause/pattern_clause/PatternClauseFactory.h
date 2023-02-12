#pragma once

#include "PatternClause.h"
#include "AssignPatternClause.h"

class PatternClauseFactory {
 public:
    static PatternClause* createPatternClause(Argument pattern, Argument left, StringExpression right);
};
