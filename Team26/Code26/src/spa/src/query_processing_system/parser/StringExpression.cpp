#include "StringExpression.h"

StringExpression::StringExpression(bool isWildcard) : isWildcard(isWildcard) {}

StringExpression::StringExpression(bool isExactMatch, std::string expression)
    : isExactMatch(isExactMatch), expression(expression) {}

std::string StringExpression::getExpression() {
    return expression;
}

bool StringExpression::matchesString(std::string str) {
    if (isWildcard) {
        // A wildcard matches anything
        return true;
    }
    return true;
}
