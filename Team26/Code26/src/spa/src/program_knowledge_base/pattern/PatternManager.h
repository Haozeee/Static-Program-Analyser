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
    std::vector<T> lhs_vector;
    std::vector<U> rhs_vector;
    std::unordered_map<int, int> index_stmt_map;
    std::unordered_map<int, int> reversed_index_stmt_map;

 public:
    bool isEmptyLhsVector() override {
        return lhs_vector.empty();
    }

    bool isEmptyRhsVector() override {
        return rhs_vector.empty();
    }

    bool isEmptyIndexStmtMap() override {
        return index_stmt_map.empty();
    }

    bool isEmptyReversedIndexStmtMap() override {
        return reversed_index_stmt_map.empty();
    }

    bool containsLhsVector(T left) override {
        bool flag = false;
        auto it = std::find(lhs_vector.begin(), lhs_vector.end(), left);
        if (it != lhs_vector.end()) {
            flag = true;
        }
        return flag;
    }

    bool containsRhsVector(U right) override {
        return std::any_of(rhs_vector.begin(), rhs_vector.end(),
                           [&](const auto& node) { return *right == *node; });
    }

    bool containsIndexStmtMap(int index, int stmt_no) override {
        bool flag = false;
        auto key = index_stmt_map.find(index);
        if (key != index_stmt_map.end()) {
            flag = key->second == stmt_no;
        }
        return flag;
    }

    bool containsReversedIndexStmtMap(int stmt_no, int index) override {
        bool flag = false;
        auto key = reversed_index_stmt_map.find(stmt_no);
        if (key != reversed_index_stmt_map.end()) {
            flag = key->second == index;
        }
        return flag;
    }

    std::unique_ptr<std::vector<T>> getAllLhsPatternEntries() override {
        return std::make_unique<std::vector<std::string>>(lhs_vector);
    }

    std::unique_ptr<std::vector<U>> getAllRhsPatternEntries() override {
        return std::make_unique<std::vector<U>>(rhs_vector);
    }

    std::unordered_map<int, int> getAllPatternEntries() override {
        return index_stmt_map;
    }

    std::unordered_map<int, int> getAllReversedPatternEntries() override {
        return reversed_index_stmt_map;
    }

    bool insertPattern(int stmt_no, T left, U right) override {
        int index = static_cast<int>(lhs_vector.size());
        lhs_vector.push_back(left);
        rhs_vector.push_back(right);
        auto x = index_stmt_map.insert({index, stmt_no});
        auto y = reversed_index_stmt_map.insert({stmt_no, index});
        return x.second && y.second;
    }
};
