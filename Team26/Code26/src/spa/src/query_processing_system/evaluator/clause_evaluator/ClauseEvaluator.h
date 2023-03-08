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

    /**
     * Checks if the result of this such that clause equates to false. The such that clause
     * is false when there are columns but no row in the ResultTable. If the such that clause is
     * false, we can set the clause results as false and we do not evaluate any other clauses in
     * the query.
     */
    void optimiseResults();

 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) = 0;
};
