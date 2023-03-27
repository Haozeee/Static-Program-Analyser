#pragma once

#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"

class ExpressionlessPatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    void evaluateSynonym() override;

    void evaluateString() override;

    void evaluateWildcard() override;

    virtual StmtEntityMap getRelationshipEntries() = 0;

    virtual EntityStmtMap getReverseRelationshipEntries() = 0;

 public:
    ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
