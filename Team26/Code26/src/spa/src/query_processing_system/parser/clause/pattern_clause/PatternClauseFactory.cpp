#include "PatternClauseFactory.h"

PatternClause* PatternClauseFactory::createPatternClause(Argument pattern, Argument left, StringExpression right) {
    if (pattern.getDesignEntity() == DesignEntity::ASSIGN) {
        return new AssignPatternClause(pattern, left, right);
    } else {
        throw QueryInvalidPatternArgument(pattern.getValue()
                                          + QueryInvalidCreatePatternArgument);
    }
}

