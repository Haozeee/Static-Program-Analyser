#include "PatternClauseFactory.h"

PatternClause* PatternClauseFactory::createPatternClause(Argument pattern, Argument left, StringExpression right) {
    if (pattern.getDesignEntity() == DesignEntity::ASSIGN) {
        return new AssignPatternClause(pattern, left, right);
    } else if (pattern.getDesignEntity() == DesignEntity::WHILE) {
        return new WhilePatternClause(pattern, left, right);
    } else if (pattern.getDesignEntity() == DesignEntity::IF) {
        return new IfPatternClause(pattern, left, right);
    } else {
        throw QueryInvalidPatternArgument(pattern.getValue()
                                          + QueryInvalidCreatePatternArgument);
    }
}

