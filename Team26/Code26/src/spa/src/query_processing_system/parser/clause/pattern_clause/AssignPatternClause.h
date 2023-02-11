#pragma once

#include "PatternClause.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/Wildcard.h"
#include "query_processing_system/parser/StringExpression.h"
#include "query_processing_system/parser/clause/Clause.h"

class AssignPatternClause : public PatternClause {
 public:
    AssignPatternClause(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
