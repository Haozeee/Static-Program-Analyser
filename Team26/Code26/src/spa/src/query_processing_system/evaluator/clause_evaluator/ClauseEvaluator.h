#pragma once
#include <memory>
#include "ClauseResult.h"
#include "../PkbUtil.h"
#include "../../../program_knowledge_base/ReadOnlyStorage.h"

using StoragePointer = std::shared_ptr<ReadOnlyStorage>;

class ClauseEvaluator {
 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ClauseResult> evaluateClause(StoragePointer storage) = 0;
};
