#pragma once
#include <memory>
#include "../PkbUtil.h"
#include "../../../program_knowledge_base/ReadOnlyStorage.h"
#include "../ResultTable.h"

using StoragePointer = std::shared_ptr<ReadOnlyStorage>;

class ClauseEvaluator {
public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) = 0;
};
