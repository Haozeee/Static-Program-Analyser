#pragma once

#include "PatternClause.h"
#include "query_processing_system/parser/StringExpression.h"
#include "query_processing_system/parser/clause/Clause.h"

class AssignPatternClause : public PatternClause {
 public:
    AssignPatternClause(Argument patternArg, Argument leftArg, StringExpression rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
