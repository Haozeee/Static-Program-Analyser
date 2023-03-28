#pragma once
#include <string>
#include "WithClauseEvaluator.h"

class StringWithClauseEvaluator : public WithClauseEvaluator<std::string> {
 private:
    /**
     * Given a reference, get its value as a string.
     */
    static EntitySet getRefValue(ProgrammeStore storage, Reference ref);

    /**
     * Given a read variable, find all read statement numbers that reads that variable.
     */
    static EntitySet getReadStatements(ProgrammeStore storage, std::string value);

    /**
     * Given a print variable, find all print statement numbers that print that variable.
     */
    static EntitySet getPrintStatements(ProgrammeStore storage, std::string value);

    /**
     * Given a procedure value, find all call statement numbers that call that procedures.
     */
    static EntitySet getCallStatements(ProgrammeStore storage, std::string value);

 protected:
    EntitySet getTranslatedValues(std::string value, DesignEntity de) override;

    EntitySet getLeftRefValues() override;

    EntitySet getRightRefValues() override;

 public:
    StringWithClauseEvaluator(Reference left, Reference right);
};
