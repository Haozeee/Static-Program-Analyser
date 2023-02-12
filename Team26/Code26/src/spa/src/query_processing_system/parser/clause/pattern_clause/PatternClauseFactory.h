#pragma once

#include "PatternClause.h"

class PatternClauseFactory {
 public:
    static PatternClause* createPatternClause(Argument, StringExpression);
};
