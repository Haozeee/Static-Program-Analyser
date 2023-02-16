#include "StringExpression.h"
#include "common/parser/ShuntNode.h"
#include "common/parser/ShuntingYardParser.h"

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
        // check partial match
        auto expressionTree = ShuntingYardParser::parse(expression);
        auto statementTree = ShuntingYardParser::parse(str);
        return ShuntNode::isSubTree(statementTree, expressionTree);
    }
}
