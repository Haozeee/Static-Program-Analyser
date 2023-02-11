#pragma once

#include <memory>
#include <variant>

#include "query_processing_system/evaluator/clause_evaluator/ClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
    DesignEntity designEntity;

    Argument leftArg;

    StringExpression rightArg;

    std::shared_ptr<ClauseResult> clauseResult;

 public:
    PatternClauseEvaluator(DesignEntity designEntity, Argument leftArg, StringExpression rightArg);

    DesignEntity getDesignEntity();

    Argument getLeftArg();

    StringExpression getRightArg();
};
