#pragma once

#include "PatternClause.h"

class PatternClauseFactory {
 public:
    static PatternClause* createPatternClause(Argument, std::variant<Wildcard, StringExpression>);
};
