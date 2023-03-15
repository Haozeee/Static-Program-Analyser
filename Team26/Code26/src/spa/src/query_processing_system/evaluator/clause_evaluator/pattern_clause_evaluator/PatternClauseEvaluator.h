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

    PatternClauseEvaluator(Argument patternArg, Argument leftArg);

    Argument patternArg;

    Argument leftArg;

    StringExpression rightArg = StringExpression(false);

    virtual void evaluateSynonym() = 0;

    virtual void evaluateString() = 0;

    virtual void evaluateWildcard() = 0;

 public:
    Argument getLeftArg();

    StringExpression getRightArg();

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage, CachePointer cache) override;
};
