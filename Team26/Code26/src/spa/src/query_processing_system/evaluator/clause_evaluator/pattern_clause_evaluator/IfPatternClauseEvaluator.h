#pragma once
#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class IfPatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    StmtEntityMap getRelationshipEntries() override;

    EntityStmtMap getReverseRelationshipEntries() override;

 public:
    IfPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
