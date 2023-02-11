#include "AssignPatternClauseFactory.h"

PatternClause* AssignPatternClauseFactory::createPatternClause(DesignEntity designEntity, Argument leftArg,
                                                               StringExpression rightArg) {
    return new AssignPatternClause(designEntity, leftArg, rightArg);
}
