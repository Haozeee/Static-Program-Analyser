#pragma once

#include "../Clause.h"
#include "Reference.h"

class WithClause : public Clause {
 private:
    Reference leftRef;

    Reference rightRef;

 public:
    WithClause(Reference left, Reference right);

    bool validateClause();

    ClauseEvaluator * getClauseEvaluator() override;
};
