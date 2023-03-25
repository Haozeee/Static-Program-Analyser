#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "StringStringClauseEvaluator.h"

class ModifiesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
