#pragma once
#include <string>
#include <unordered_set>
#include "WithClauseEvaluator.h"

using IntSet = std::unordered_set<int>;

class IntWithClauseEvaluator : public WithClauseEvaluator<int> {
 private:
    static IntSet getRefValue(StoragePointer storage, Reference ref);

 protected:
    std::unordered_set<std::string> getTranslatedValues(int value, DesignEntity de) override;

    IntSet getLeftRefValues() override;

    IntSet getRightRefValues() override;

 public:
    IntWithClauseEvaluator(Reference left, Reference right);
};
