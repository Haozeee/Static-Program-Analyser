#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "ReadOnlyPatternManager.h"
#include "WriteOnlyPatternManager.h"

class PatternManager: public ReadyOnlyPatternManager, public WriteOnlyPatternManager {
 private:
    std::vector<std::string> lhs;
    std::vector<std::string> rhs;
    std::unordered_map<int, int> index_stmt_map;
    std::unordered_map<int, int> reversed_index_stmt_map;

 public:
    bool insert(int stmt_no, std::string left, std::string right) {
        int index = lhs.size();
        lhs.push_back(left);
        rhs.push_back(right);
        auto x = index_stmt_map.insert({index, stmt_no});
        auto y = reversed_index_stmt_map.insert({stmt_no, index});
        return x.second && y.second;
    }
};
