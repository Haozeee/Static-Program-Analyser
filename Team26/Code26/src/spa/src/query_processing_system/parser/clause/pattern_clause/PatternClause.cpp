#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(Argument patternArg, Argument left, StringExpression right)
        : patternArg(std::move(patternArg)), leftArg(std::move(left)), rightArg(std::move(right)) {}

Argument PatternClause::getPatternArg() {
    return patternArg;
}

Argument PatternClause::getLeftArg() {
    return leftArg;
}

StringExpression PatternClause::getRightArg() {
    return rightArg;
}

std::unordered_set<ArgumentType> PatternClause::getValidLeftArgumentType() {
    return std::unordered_set<ArgumentType> {
            ArgumentType::SYNONYM,
            ArgumentType::WILDCARD,
            ArgumentType::CHARACTERSTRING,
    };
}

PatternClauseValidationResult PatternClause::isValidClause() {
    if (!getValidLeftArgumentType().count(leftArg.getArgumentType())) {
        return PatternClauseValidationResult::INVALID_LEFT_ARG_TYPE;
    }
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM &&
        leftArg.getDesignEntity() != DesignEntity::VARIABLE) {
        return PatternClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY;
    }
    return PatternClauseValidationResult::VALID;
}
