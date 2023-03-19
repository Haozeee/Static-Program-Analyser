#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "common/parser/ShuntNode.h"

template <typename T, typename U>
class IReadPatternManager {
 public:
    virtual bool isEmptyLhsVector() = 0;
    virtual bool isEmptyRhsVector() = 0;
    virtual bool isEmptyIndexStmtMap() = 0;
    virtual bool isEmptyReversedIndexStmtMap() = 0;
    virtual bool containsLhsVector(T left) = 0;
    virtual bool containsRhsVector(U right) = 0;
    virtual bool containsIndexStmtMap(int index, int stmtNo) = 0;
    virtual bool containsReversedIndexStmtMap(int stmtNo, int index) = 0;
    virtual std::unique_ptr<std::vector<T>> getAllLhsPatternEntries() = 0;
    virtual std::unique_ptr<std::vector<U>> getAllRhsPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllReversedPatternEntries() = 0;
};
