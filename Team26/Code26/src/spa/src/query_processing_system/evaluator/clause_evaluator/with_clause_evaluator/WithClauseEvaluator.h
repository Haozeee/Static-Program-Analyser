#pragma once

#include "../ClauseEvaluator.h"
#include "../../../parser/clause/with_clause/Reference.h"

class WithClauseEvaluator : public ClauseEvaluator {
 protected:
    Reference leftRef;

    Reference rightRef;

 public:
    WithClauseEvaluator(Reference left, Reference right);

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
