#pragma once

#include <memory>
#include <variant>
#include "query_processing_system/evaluator/clause_evaluator/ClauseEvaluator.h"
#include "query_processing_system/evaluator/PkbUtil.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
    PatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);

    Argument patternArg;

    Argument leftArg;

    StringExpression rightArg;

    virtual void evaluateSynonym(std::shared_ptr<ReadStorage>) = 0;

    virtual void evaluateString(std::shared_ptr<ReadStorage>) = 0;

    virtual void evaluateWildcard(std::shared_ptr<ReadStorage>) = 0;

 public:
    Argument getLeftArg();

    StringExpression getRightArg();
};
