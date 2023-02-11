#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg)
    : PatternClauseEvaluator(leftArg, rightArg) {}
