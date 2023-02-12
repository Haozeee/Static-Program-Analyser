#include "StringExpression.h"

StringExpression::StringExpression(bool isWildcard) : isWildcard(isWildcard) {}

StringExpression::StringExpression(bool isExactMatch, std::string expression)
    : isExactMatch(isExactMatch), expression(expression) {}

bool StringExpression::getIsWildcard() {
    return isWildcard;
}

bool StringExpression::getIsExactMatch() {
    return isExactMatch;
}

std::string StringExpression::getExpression() {
    return expression;
}
