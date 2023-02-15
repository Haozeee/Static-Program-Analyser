#pragma once

#include <utility>
#include <variant>
#include <unordered_set>

#include "query_processing_system/parser/clause/Clause.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"
#include "PatternClauseValidationResult.h"

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

 protected:
    PatternClause(Argument patternArg, Argument leftArg, StringExpression rightArg);

    std::unordered_set<ArgumentType> getValidLeftArgumentType();

 public:
    virtual ~PatternClause() = default;

    PatternClauseValidationResult isValidClause();

    Argument getPatternArg();

    Argument getLeftArg();

    StringExpression getRightArg();
};
