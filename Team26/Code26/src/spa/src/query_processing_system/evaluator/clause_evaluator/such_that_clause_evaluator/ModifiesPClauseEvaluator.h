#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class ModifiesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
