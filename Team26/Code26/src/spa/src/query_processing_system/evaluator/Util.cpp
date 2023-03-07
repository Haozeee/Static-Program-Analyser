#include "Util.h"

std::unordered_set<std::string> Util::intSetToStringSet(std::unordered_set<int> intSet) {
    std::unordered_set<std::string>  result;
    std::transform(intSet.begin(), intSet.end(), std::inserter(result, result.begin()),
                   [](int i) {return std::to_string(i);});
    return result;
}


std::unordered_map<std::string, std::unordered_set<std::string>>
Util::intMapTostringMap(std::unordered_map<int, std::unordered_set<int>> &intMap) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    for (auto const& [k, v] : intMap) {
        res.insert({std::to_string(k), intSetToStringSet(v)});
    }
    return res;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
Util::intStringMapTostringMap(std::unordered_map<int, std::unordered_set<std::string>> &intMap) {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    for (auto const& [k, v] : intMap) {
        res.insert({std::to_string(k), v});
    }
    return res;
}
