#pragma once

#include <memory>

#include "query_processing_system/evaluator/clause_evaluator/ClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/Wildcard.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument leftArg;

    std::variant<Wildcard, StringExpression> rightArg;

    std::shared_ptr<ClauseResult> clauseResult;

 public:
    PatternClauseEvaluator(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg);

    Argument getLeftArg();

    std::variant<Wildcard, StringExpression> getRightArg();
};
