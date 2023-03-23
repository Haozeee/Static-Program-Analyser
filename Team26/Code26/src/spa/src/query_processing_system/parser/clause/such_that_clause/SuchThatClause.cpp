#include "SuchThatClause.h"
#include <utility>

SuchThatClause::SuchThatClause(Argument left, Argument right)
    : leftArg(std::move(left)), rightArg(std::move(right)) {}

Argument SuchThatClause::getLeftArg() {
    return leftArg;
}

Argument SuchThatClause::getRightArg() {
    return rightArg;
}

SuchThatClauseValidationResult SuchThatClause::isValidClause() {
    if (!getValidLeftArgumentType().count(leftArg.getArgumentType())) {
        return SuchThatClauseValidationResult::INVALID_LEFT_ARG_TYPE;
    }
    if (!getValidRightArgumentType().count(rightArg.getArgumentType())) {
        return SuchThatClauseValidationResult::INVALID_RIGHT_ARG_TYPE;
    }
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM &&
        !getValidLeftDesignEntity().count(leftArg.getDesignEntity())) {
        return SuchThatClauseValidationResult::INVALID_LEFT_DESIGN_ENTITY;
    }
    if (rightArg.getArgumentType() == ArgumentType::SYNONYM &&
        !getValidRightDesignEntity().count(rightArg.getDesignEntity())) {
        return SuchThatClauseValidationResult::INVALID_RIGHT_DESIGN_ENTITY;
    }
    return SuchThatClauseValidationResult::VALID;
}

int SuchThatClause::getOptimisationPoints() {
    int points = 0;

    if (leftArg.getArgumentType() == ArgumentType::SYNONYM) {
        points += 1;
    } else if (leftArg.getArgumentType() == ArgumentType::WILDCARD) {
        points += 2;
    }

    if (rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        points += 1;
    } else if (rightArg.getArgumentType() == ArgumentType::WILDCARD) {
        points += 2;
    }

    return points;
}
