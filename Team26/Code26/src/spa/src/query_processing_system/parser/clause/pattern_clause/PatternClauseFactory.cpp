#include "PatternClauseFactory.h"

PatternClause* createPatternClause(Argument left, std::variant<Wildcard, StringExpression> right);
