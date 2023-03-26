#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>
#include "IReadPatternManager.h"
#include "IWritePatternManager.h"
#include "common/parser/ShuntNode.h"

template <typename T, typename U>
class PatternManager: public IReadPatternManager<T, U>, public IWritePatternManager<T, U> {
 private:
    std::vector<T> lhsVector;
    std::vector<U> rhsVector;
    std::unordered_map<int, int> indexStmtMap;
    std::unordered_map<int, int> reversedIndexStmtMap;

 public:
    bool isEmptyLhsVector() override {
        return lhsVector.empty();
    }

    bool isEmptyRhsVector() override {
        return rhsVector.empty();
    }

    bool isEmptyIndexStmtMap() override {
        return indexStmtMap.empty();
    }

    bool isEmptyReversedIndexStmtMap() override {
        return reversedIndexStmtMap.empty();
    }

    bool containsLhsVector(T left) override {
        bool flag = false;
        auto it = std::find(lhsVector.begin(), lhsVector.end(), left);
        if (it != lhsVector.end()) {
            flag = true;
        }
        return flag;
    }

    bool containsRhsVector(U right) override {
        return std::any_of(rhsVector.begin(), rhsVector.end(),
                           [&](const auto& node) { return *right == *node; });
    }

    bool containsIndexStmtMap(int index, int stmtNo) override {
        auto key = indexStmtMap.find(index);
        if (key != indexStmtMap.end()) {
            return key->second == stmtNo;
        } else {
            return false;
        }
    }

    bool containsReversedIndexStmtMap(int stmtNo, int index) override {
        auto key = reversedIndexStmtMap.find(stmtNo);
        if (key != reversedIndexStmtMap.end()) {
            return key->second == index;
        } else {
            return false;
        }
    }

    std::unique_ptr<std::vector<T>> getAllLhsPatternEntries() override {
        return std::make_unique<std::vector<std::string>>(lhsVector);
    }

    std::unique_ptr<std::vector<U>> getAllRhsPatternEntries() override {
        return std::make_unique<std::vector<U>>(rhsVector);
    }

    std::unordered_map<int, int> getAllPatternEntries() override {
        return indexStmtMap;
    }

    std::unordered_map<int, int> getAllReversedPatternEntries() override {
        return reversedIndexStmtMap;
    }

    bool insertPattern(int stmtNo, T left, U right) override {
        int index = static_cast<int>(lhsVector.size());
        lhsVector.push_back(left);
        rhsVector.push_back(right);

        auto insertedIndexStmtMap = indexStmtMap.insert({index, stmtNo});
        bool flag1 = insertedIndexStmtMap.second;
        auto insertedReversedIndexStmtMap = reversedIndexStmtMap.insert({stmtNo, index});
        bool flag2 = insertedReversedIndexStmtMap.second;

        return flag1 && flag2;
    }
};
