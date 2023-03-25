#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsTClauseEvaluator : public StringStringClauseEvaluator {
 protected:
    EntityEntityMap getRelationshipMap(EntitySet &interestedValues) override;

    EntityEntityMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    CallsTClauseEvaluator(Argument left, Argument right);
};
