#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class UsesPClauseEvaluator : public StringStringClauseEvaluator {
 protected:
    EntityEntityMap getRelationshipMap(EntitySet &interestedValues) override;

    EntityEntityMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    UsesPClauseEvaluator(Argument left, Argument right);
};
