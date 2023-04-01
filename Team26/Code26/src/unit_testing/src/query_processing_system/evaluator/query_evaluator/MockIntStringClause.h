#pragma once

#include "query_processing_system/parser/clause/such_that_clause/IntStringClause.h"

class MockIntStringClause: public IntStringClause {
 public:
    MockIntStringClause(Argument left, Argument right);

    ClauseEvaluator* getClauseEvaluator() override;
};
