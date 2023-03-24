#pragma once
#include <memory>
#include "cache/Cache.h"
#include "../PkbUtil.h"
#include "../Util.h"
#include "../../../program_knowledge_base/StorageManager.h"
#include "../ResultTable.h"

using StoragePointer = std::shared_ptr<ReadStorage>;

using CachePointer = std::shared_ptr<Cache>;

class ClauseEvaluator {
 protected:
    std::shared_ptr<ResultTable> clauseResultTable = std::make_shared<ResultTable>();

    StoragePointer storage;

    CachePointer cache;

    /**
     * Checks if the result of this such that clause equates to false. The such that clause
     * is false when there are columns but no row in the ResultTable. If the such that clause is
     * false, we can set the clause results as false and we do not evaluate any other clauses in
     * the query.
     */
    void optimiseResults();

    virtual void setStorageLocation(StoragePointer storage_, CachePointer cache_);

 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage, CachePointer cache) = 0;
};
