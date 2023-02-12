#pragma once

#include <utility>
#include <variant>

#include "query_processing_system/parser/clause/Clause.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClause : public Clause {
 private:
    /**
     * Given a clause "pattern a(v, "x+y")",
     * patternArg = a
     * leftArg = v
     * rightArg = "x+y"
     */
    Argument patternArg;

    Argument leftArg;

    StringExpression rightArg;

 public:
    PatternClause(Argument patternArg, Argument leftArg, StringExpression rightArg);

    virtual ~PatternClause() = default;

    Argument getPatternArg();

    Argument getLeftArg();

    StringExpression getRightArg();
};
