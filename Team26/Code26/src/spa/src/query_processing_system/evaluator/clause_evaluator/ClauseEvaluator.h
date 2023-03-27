#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "RelationResultType.h"
#include "ISourceReader.h"
#include "../Util.h"
#include "../ResultTable.h"

using ProgrammeStore = std::shared_ptr<ISourceReader>;

class ClauseEvaluator {
 protected:
    std::shared_ptr<ResultTable> clauseResultTable = std::make_shared<ResultTable>();

    ProgrammeStore storage;

    /**
     * Checks if the result of this such that clause equates to false. The such that clause
     * is false when there are columns but no row in the ResultTable. If the such that clause is
     * false, we can set the clause results as false and we do not evaluate any other clauses in
     * the query.
     */
    void optimiseResults();

    virtual void setStorageLocation(ProgrammeStore storage_);

 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual std::shared_ptr<ResultTable> evaluateClause(ProgrammeStore storage) = 0;
};
