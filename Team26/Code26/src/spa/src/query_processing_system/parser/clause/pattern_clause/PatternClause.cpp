#include "PatternClause.h"

PatternClause::PatternClause(DesignEntity designEntity, Argument left, StringExpression right)
        : designEntity(designEntity), leftArg(std::move(left)), rightArg(std::move(right)) {}

DesignEntity PatternClause::getDesignEntity() {
    return designEntity;
}
Argument PatternClause::getLeftArg() {
    return leftArg;
}

StringExpression PatternClause::getRightArg() {
    return rightArg;
}
