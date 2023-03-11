#pragma once

#include <string>
#include <memory>
#include "common/parser/ShuntNode.h"
#include "common/parser/ShuntingYardParser.h"

/**
 * This is for the second argument of the Assign Pattern Clause.
 * StringExpression for exact match (e.g. "x*y")
 *      -> Means do not have wildcard on either side of expression
 * StringExpression for partial match (e.g. _"x*y"_)
 *      -> Have wildcard on both sides of expression
 */
class StringExpression {
 private:
    /**
     * Whether the expression is a Wildcard, represented by '_'.
     */
    bool isWildcard = false;

    /**
     * Whether the expression is an exact or partial match.
     */
    bool isExactMatch;

    /**
     * The expression itself.
     */
    std::string expression;

 public:
    explicit StringExpression(bool isWildcard);

    StringExpression(bool isExactMatch, std::string expression);

    /**
     * Checks if this string expression matches a statement tree produced by the
     * shunting yard parser.
     */
    bool matchesStatementTree(std::shared_ptr<ShuntNode> statementTree);

    std::string getExpression();

    bool isWildCard();

    void setIsWildCard();
};
