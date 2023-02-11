#pragma once

#include <utility>

#include "query_processing_system/parser/clause/Clause.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/Wildcard.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClause: public Clause {
 private:
    Argument leftArg;

    std::variant<Wildcard, StringExpression> rightArg;

 public:
    PatternClause(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg);

    virtual ~PatternClause() = default;

    Argument getLeftArg();

    std::variant<Wildcard, StringExpression> getRightArg();
};
