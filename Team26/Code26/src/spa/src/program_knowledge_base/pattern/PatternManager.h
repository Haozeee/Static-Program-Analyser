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


class PatternManager: public IReadPatternManager, public IWritePatternManager {
 private:
    std::vector<std::string> lhs_vector;
    std::vector<const std::shared_ptr<ShuntNode>> rhs_vector;
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

    bool containsLhsVector(const std::string& left) override {
        auto it = std::find(lhs_vector.begin(), lhs_vector.end(), left);
        if (it != lhs_vector.end()) {
            return true;
        }
        return false;
    }

    bool containsRhsVector(std::shared_ptr<ShuntNode> right) override {
        return std::any_of(rhs_vector.begin(), rhs_vector.end(),
                           [&](const auto& node) { return *right == *node; });
    }

    bool containsIndexStmtMap(int index, int stmt_no) override {
        auto key = index_stmt_map.find(index);
        if (key != index_stmt_map.end()) {
            return key->second == stmt_no;
        }
        return false;
    }

    bool containsReversedIndexStmtMap(int stmt_no, int index) override {
        auto key = reversed_index_stmt_map.find(stmt_no);
        if (key != reversed_index_stmt_map.end()) {
            return key->second == index;
        }
        return false;
    }

    std::vector<std::string> getAllLhsPatternEntries() override {
        return lhs_vector;
    }

    std::vector<const std::shared_ptr<ShuntNode>> getAllRhsPatternEntries() override {
        return rhs_vector;
    }

    std::unordered_map<int, int> getAllPatternEntries() override {
        return index_stmt_map;
    }

    std::unordered_map<int, int> getAllReversedPatternEntries() override {
        return reversed_index_stmt_map;
    }

    bool insertPattern(int stmt_no, std::string left, std::shared_ptr<ShuntNode> right) override {
        int index = static_cast<int>(lhs_vector.size());
        lhs_vector.push_back(left);
        rhs_vector.push_back(right);
        auto x = index_stmt_map.insert({index, stmt_no});
        auto y = reversed_index_stmt_map.insert({stmt_no, index});
        return x.second && y.second;
    }
};
