#pragma once
#include <string>
#include "WithClauseEvaluator.h"

class IntWithClauseEvaluator : public WithClauseEvaluator<int> {
 private:
    static StmtSet getRefValue(ProgrammeStore storage, Reference ref);

 protected:
    EntitySet getTranslatedValues(int value, DesignEntity de) override;

    StmtSet getLeftRefValues() override;

    StmtSet getRightRefValues() override;

 public:
    IntWithClauseEvaluator(Reference left, Reference right);
};
