#pragma once
#include <memory>
#include "ClauseResult.h"
#include "../../../program_knowledge_base/ReadOnlyStorage.h"

class ClauseEvaluator {
 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) = 0;
};
