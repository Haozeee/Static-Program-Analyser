#pragma once

#include <memory>
#include <variant>

#include "query_processing_system/evaluator/clause_evaluator/ClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument patternArg;

    Argument leftArg;

    StringExpression rightArg;

    std::shared_ptr<ResultTable> clauseResultTable;

 public:
    PatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);

    Argument getLeftArg();

    StringExpression getRightArg();
};
