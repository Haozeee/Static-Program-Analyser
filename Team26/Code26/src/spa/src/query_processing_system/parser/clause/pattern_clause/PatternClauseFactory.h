#pragma once

#include "PatternClause.h"
#include "AssignPatternClause.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"

class PatternClauseFactory {
 public:
    static PatternClause* createPatternClause(Argument pattern, Argument left, StringExpression right);
};
