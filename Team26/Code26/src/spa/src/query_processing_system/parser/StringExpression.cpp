#include "StringExpression.h"

StringExpression::StringExpression(bool isWildcard) : isWildcard(isWildcard) {}

StringExpression::StringExpression(bool isExactMatch, std::string expression)
    : isExactMatch(isExactMatch), expression(expression), isWildcard(false) {}

std::string StringExpression::getExpression() {
    return expression;
}

bool StringExpression::matchesStatementTree(std::shared_ptr<ShuntNode> statementTree) {
    if (isWildcard) {
        // A wildcard matches anything
        return true;
    }
    auto expressionTree = ShuntingYardParser::parse(expression);
    if (isExactMatch) {
        return *statementTree == *expressionTree;
    } else {
        // check partial match
        return ShuntNode::isSubTree(statementTree, expressionTree);
    }
}

bool StringExpression::isWildCard() {
    return isWildcard;
}
