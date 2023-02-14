#include "StringExpression.h"

StringExpression::StringExpression(bool isWildcard) : isWildcard(isWildcard) {}

StringExpression::StringExpression(bool isExactMatch, std::string expression)
    : isExactMatch(isExactMatch), expression(expression), isWildcard(false) {}

std::string StringExpression::getExpression() {
    return expression;
}

bool StringExpression::matchesString(std::string str) {
    if (isWildcard) {
        // A wildcard matches anything
        return true;
    }
    if (isExactMatch) {
        return str == expression;
    } else {
        // check if expression is a substring of str
        return str.find(expression) != std::string::npos;
    }
}
