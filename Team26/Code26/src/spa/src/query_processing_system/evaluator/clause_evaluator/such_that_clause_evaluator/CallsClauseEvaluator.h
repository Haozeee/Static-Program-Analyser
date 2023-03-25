#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsClauseEvaluator : public StringStringClauseEvaluator {
 protected:
    EntityEntityMap getRelationshipMap(EntitySet &interestedValues) override;

    EntityEntityMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

public:
    CallsClauseEvaluator(Argument left, Argument right);
};
