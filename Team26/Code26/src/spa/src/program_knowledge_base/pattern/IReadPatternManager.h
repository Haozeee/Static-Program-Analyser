#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "common/parser/ShuntNode.h"

class IReadPatternManager {
 public:
    virtual bool isEmptyLhsVector() = 0;
    virtual bool isEmptyRhsVector() = 0;
    virtual bool isEmptyIndexStmtMap() = 0;
    virtual bool isEmptyReversedIndexStmtMap() = 0;
    virtual bool containsLhsVector(const std::string&) = 0;
    virtual bool containsRhsVector(std::shared_ptr<ShuntNode>) = 0;
    virtual bool containsIndexStmtMap(int, int) = 0;
    virtual bool containsReversedIndexStmtMap(int, int) = 0;
    virtual std::unique_ptr<std::vector<std::string>> getAllLhsPatternEntries() = 0;
    virtual std::unique_ptr<std::vector<std::shared_ptr<ShuntNode>>> getAllRhsPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllReversedPatternEntries() = 0;
};
