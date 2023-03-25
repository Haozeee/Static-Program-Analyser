#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class ModifiesPClauseEvaluator : public StringStringClauseEvaluator {
 protected:
    EntityEntityMap getRelationshipMap(EntitySet &interestedValues) override;

    EntityEntityMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);
};
