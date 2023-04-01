#pragma once

#include "query_processing_system/parser/clause/such_that_clause/IntIntClause.h"

class MockIntIntClause : public IntIntClause {
public:
    MockIntIntClause (Argument left, Argument right);

    ClauseEvaluator* getClauseEvaluator() override;
};