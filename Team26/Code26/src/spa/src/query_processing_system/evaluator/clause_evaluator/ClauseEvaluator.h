#pragma once
#include <memory>
#include "../PkbUtil.h"
#include "../Util.h"
#include "../../../program_knowledge_base/StorageManager.h"
#include "../ResultTable.h"

using StoragePointer = std::shared_ptr<ReadStorage>;

class ClauseEvaluator {
 protected:
    std::shared_ptr<ResultTable> clauseResultTable = std::make_shared<ResultTable>();

 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) = 0;
};
