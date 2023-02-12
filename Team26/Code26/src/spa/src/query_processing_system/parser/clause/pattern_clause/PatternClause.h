#pragma once

#include <utility>
#include <variant>

#include "query_processing_system/parser/clause/Clause.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/StringExpression.h"

class PatternClause : public Clause {
 private:
    DesignEntity designEntity;

    Argument leftArg;

    StringExpression rightArg;

 public:
    PatternClause(DesignEntity designEntity, Argument leftArg, StringExpression rightArg);

    virtual ~PatternClause() = default;

    DesignEntity getDesignEntity();

    Argument getLeftArg();

    StringExpression getRightArg();
};
