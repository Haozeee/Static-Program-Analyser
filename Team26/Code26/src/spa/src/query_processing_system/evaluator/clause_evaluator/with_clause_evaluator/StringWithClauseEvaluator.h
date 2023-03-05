#pragma once
#include <string>
#include <unordered_set>
#include "WithClauseEvaluator.h"

using StringSet = std::unordered_set<std::string>;

class StringWithClauseEvaluator : public WithClauseEvaluator<std::string> {
 private:
    /**
     * Given a reference, get its value as a string.
     */
    static StringSet getRefValue(StoragePointer storage, Reference ref);

    /**
     * Given a read variable, find all read statement numbers that reads that variable.
     */
    static StringSet getReadStatements(StoragePointer storage, std::string value);

    /**
     * Given a print variable, find all print statement numbers that print that variable.
     */
    static StringSet getPrintStatements(StoragePointer storage, std::string value);

    /**
     * Given a procedure value, find all call statement numbers that call that procedures.
     */
    static StringSet getCallStatements(StoragePointer storage, std::string value);

 protected:
    StringSet getTranslatedValues(StoragePointer storage, std::string value, DesignEntity de) override;

    StringSet getLeftRefValues(StoragePointer storage) override;

    StringSet getRightRefValues(StoragePointer storage) override;

 public:
    StringWithClauseEvaluator(Reference left, Reference right);
};
