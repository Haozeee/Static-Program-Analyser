#pragma once

#include <unordered_set>
#include "query_processing_system/parser/clause/such_that_clause/StringStringClause.h"

class MockStringStringClause: public StringStringClause {
 public:
    MockStringStringClause(Argument left, Argument right);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
