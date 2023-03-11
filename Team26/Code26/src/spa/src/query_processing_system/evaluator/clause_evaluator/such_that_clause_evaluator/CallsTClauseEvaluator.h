#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsTClauseEvaluator : public StringStringClauseEvaluator {
 public:
    CallsTClauseEvaluator(Argument left, Argument right);

    std::unordered_map<std::string , std::unordered_set<std::string>>
    getRelationshipManager() override;

    std::unordered_map<std::string, std::unordered_set<std::string>>
    getOppositeRelationshipManager() override;

    void handleRightWildcard() override;
};
