#pragma once
#include <memory>
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"

enum class ClauseArgumentTypes {
    NUMBER_NUMBER,
    SYNONYM_NUMBER,
    NUMBER_SYNONYM,
    SYNONYM_SYNONYM,
    NONE
};

class SuchThatClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument leftArg;

    Argument rightArg;

    std::shared_ptr<ClauseResult> clauseResult;

    ClauseArgumentTypes getClauseArgumentTypes();

 public:
    SuchThatClauseEvaluator(Argument left, Argument right);

    Argument getLeftArg();

    Argument getRightArg();
};
