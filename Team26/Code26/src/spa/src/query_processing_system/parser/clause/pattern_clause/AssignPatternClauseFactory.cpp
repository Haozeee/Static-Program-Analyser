#include "AssignPatternClauseFactory.h"

PatternClause* AssignPatternClauseFactory::createPatternClause(Argument leftArg,
                                                                           std::variant<Wildcard, StringExpression> rightArg) {
    return new AssignPatternClause(leftArg, rightArg);
}