#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "StringStringClauseEvaluator.h"

class ModifiesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);
    
    std::unordered_map<std::string , std::unordered_set<std::string>>
    getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<std::string, std::unordered_set<std::string>>
    getOppositeRelationshipManager(StoragePointer storage) override;
};
