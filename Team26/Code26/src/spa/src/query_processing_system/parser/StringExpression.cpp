#include "StringExpression.h"

StringExpression::StringExpression(bool isExactMatch, std::string expression)
    : isExactMatch(isExactMatch), expression(expression) {}

bool StringExpression::getIsExactMatch() {
    return isExactMatch;
}

std::string StringExpression::getExpression() {
    return expression;
}
