#pragma once

#include "PatternClause.h"
#include "query_processing_system/parser/StringExpression.h"
#include "query_processing_system/parser/clause/Clause.h"

class IfPatternClause : public PatternClause {
public:
    IfPatternClause(Argument patternArg, Argument leftArg, StringExpression rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
